#include <iostream>
using namespace std;

#include "GameScreen.hpp"

GameScreen::GameScreen() : Screen()
{
    
}

GameScreen::GameScreen(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer) : Screen(tex, src, dst, a)
{
    // this->wordSprite->loadFromFile("res/img/wordSprite.png", gRenderer);
    score = 0;
    money = 450;

    cout << "In GameScreen constructor\nLoading word" << endl;
    this->wordSprite.loadFromFile("res/img/wordSprite.png", gRenderer);
    cout << "Loaded word" << endl;

    buttons.push_back(Button( &wordSprite, "Shop", SCREEN_WIDTH - 160, 40 ));
    buttons.push_back(Button( &wordSprite, "End", SCREEN_WIDTH - 160, 105 ));
    buttons.push_back(Button( &wordSprite, "Put Mask", SCREEN_WIDTH - 230, 185 ));
    buttons.push_back(Button( &wordSprite, "Sanitize", SCREEN_WIDTH - 230, 255 ));    

    // Word(string text, LTexture* image, float x, float y)
    scoreWordLetters = Word("Score  ", &wordSprite, 140, 40); 
    timeWordLetters = Word("Time  ", &wordSprite, 140, 105);

    timeWord = Word("60", &wordSprite, 240, 101);
    scoreWord = Word("0", &wordSprite, 240, 37);

    maskTexture.loadFromFile("res/img/mask_single.png", gRenderer);
    SDL_Rect maskSrcRect = {0,0,396,274};
    SDL_Rect maskDstRect = {SCREEN_WIDTH/2 - 220,10,60,50};
    mask = Mask(&maskTexture, maskSrcRect, maskDstRect);

    sanitizerTexture.loadFromFile("res/img/sanitizer.png", gRenderer);
    SDL_Rect sanitizerSrcRect = {0,0,200,373};
    SDL_Rect sanitizerDstRect = {SCREEN_WIDTH/2 - 210,70,40,60};
    sanitizer = Sanitizer(&sanitizerTexture, sanitizerSrcRect, sanitizerDstRect);

    noOfMasksWord = Word("0", &wordSprite, SCREEN_WIDTH/2 + 40 - 150, 37);
    noOfSanitizerWord = Word("0", &wordSprite, SCREEN_WIDTH/2 + 40 - 150, 101);

    crossTexture.loadFromFile("res/img/cross_final.png", gRenderer);

    SDL_Rect crossSrcRect = {0,0,0,0};  // this is trivial here bcz hardcoded in constructor
    SDL_Rect crossDstRect[TOTAL_CROSSES];
    crossDstRect[0] = {150,600,60,60};
    crossDstRect[1] = {150+312,600,60,60};
    crossDstRect[2] = {150+312+312,600,60,60};
    crossDstRect[3] = {150+312+312+312,600,60,60};

    for (int i=0; i < TOTAL_CROSSES; i++)
    {
        crosses.push_back( Cross(&crossTexture, crossSrcRect, crossDstRect[i] ));
    }

    SDL_Rect playerSrcRect = {0,0,0,0};
    playerTexture.loadFromFile("res/img/person.png", gRenderer);
    player = Player(&playerTexture, playerSrcRect, playerSrcRect);

    playerMaskedTexture.loadFromFile("res/img/person_masked.png", gRenderer);

    SDL_Rect moneySrc = {0,0, 394, 430};
    SDL_Rect moneyDst = {SCREEN_WIDTH/2 + 40 + 30, 10, 50, 54};
    moneyTexture.loadFromFile("res/img/money.png", gRenderer);
    moneyPicture = Entity(&moneyTexture, moneySrc, moneyDst);
    moneyWord = Word("0", &wordSprite, SCREEN_WIDTH/2 + 40 + 130, 37);

    warningBorder.loadFromFile("res/img/warning.png", gRenderer);

    maskWarn = Word("Wear a mask!", &wordSprite, SCREEN_WIDTH/2 - 390, 190);
    maskUpTimeWord = Word("Mask uptime ", &wordSprite, SCREEN_WIDTH/2 - 380,190 );
    sanitizerWarn = Word("Sanitize your hands!", &wordSprite, SCREEN_WIDTH/2 - 275, 260);
    sanitizerUpTimeWord = Word("Sanitizer uptime ", &wordSprite, SCREEN_WIDTH/2 - 275, 260);

    standWarn = Word("Stand on a Mark!", &wordSprite, SCREEN_WIDTH/2 - 320, 330);
}

void GameScreen::renderGameScreen(SDL_Renderer* gRenderer)
{
    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);

    SDL_Rect screenSrcDstRect = {0,0,1248,702};

    if ( !(player.isWearingMask) | !(player.isSanitized) | !(player.isStandingOnMark) )
    {
        warningBorder.render(0,0,&screenSrcDstRect,0.0,NULL,SDL_FLIP_NONE,gRenderer,1,&screenSrcDstRect);
    }

    buttons[0].render(gRenderer, true);
    buttons[1].render(gRenderer, true);
    buttons[2].render(gRenderer, false);
    buttons[3].render(gRenderer, false);

    scoreWordLetters.render(gRenderer);
    timeWordLetters.render(gRenderer);
    timeWord.render(gRenderer);

    string tempScoreWord = to_string(score);
    scoreWord.changeWord(tempScoreWord);
    scoreWord.render(gRenderer);

    mask.renderMask(gRenderer);
    sanitizer.renderSanitizer(gRenderer);

    noOfMasksWord.render(gRenderer);
    noOfSanitizerWord.render(gRenderer);

    for (int i=0; i < TOTAL_CROSSES; i++)
    {
        crosses[ i ].renderCross(gRenderer);
    }

    if (player.isWearingMask)
    {
        player.setTexture(&playerMaskedTexture);
        // add change word statement -> done
        string tempMaskTime = to_string( mask.timeEffective - (int) (maskUpTime.getTicks() / 1000.f) );
        maskUpTimeWord.changeWord("Mask uptime " + tempMaskTime );
        maskUpTimeWord.render(gRenderer);
    }
    else
    {
        player.setTexture(&playerTexture);
        maskWarn.render(gRenderer);
    }

    if ( !(player.isSanitized) )
    {
        sanitizerWarn.render(gRenderer);
    }
    else if ( player.isSanitized )
    {
        // add -> done
        string tempSanitizeTime = to_string( sanitizer.timeEffective - (int) (sanitizerUpTime.getTicks() / 1000.f) );

        sanitizerUpTimeWord.changeWord("Sanitizer uptime " +  tempSanitizeTime);

        sanitizerUpTimeWord.render(gRenderer);
    }

    if ( !(player.isStandingOnMark) )
    {
        standWarn.render(gRenderer);
    }

    player.renderPlayer(gRenderer);

    string tempMoneyWord = to_string(money);
    moneyWord.changeWord(tempMoneyWord);
    moneyWord.render(gRenderer);

    moneyPicture.render(gRenderer);

}

void GameScreen::handleEvents(SDL_Event& e, Screen* mainMenu, Screen* shop)
{
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        for (int i =0; i< this->noOfButtons ; i++)
        {
            if (buttons[i].cursorOverIt(x,y, false))
            {
                buttons[i].state = 1;
                if (! buttons[i].playedMusic )
                    Mix_PlayChannel( -1, this->gButtonHover, 0 );
                buttons[i].playedMusic = 1;
            }
            else
            {
                buttons[i].state = 0;
                buttons[i].playedMusic = 0;
            }
        }
        if(e.type == SDL_MOUSEBUTTONDOWN) // change the click position of the mouse
        {
            if (e.button.button == SDL_BUTTON_LEFT) // Undo Button
            {
                for (int i=0; i< this->noOfButtons; i++)
                {
                    if (buttons[i].cursorOverIt(x,y, true))
                    {
                        this->selectedOption = i;
                        Mix_PlayChannel( -1, this->gButtonClick, 0 );
                        this->analyzeOption(mainMenu, shop);
                        break;
                    }
                }
            }
        }

        for (int i=0; i < TOTAL_CROSSES; i++)
        {
            crosses[ i ].handleEvent(&e, &player);
        }
    }
}

void GameScreen::analyzeOption(Screen* mainMenu, Screen* shop)
{
    if (selectedOption == 0)
    {
        this->alive = false;
        shop->setAlive(true);
    }
    else if (selectedOption == 1)
    {
        this->alive = false;
        this->endGame();
        mainMenu->setAlive(true);
    }
    else if (selectedOption == 2)
    {
        // mask up
        if (this->noOfMasks >= 1)
        {
            if (player.isWearingMask == false)
                this->score += 5;          // only increase score if player was not masked but use resources if button pressed extra times
            
            player.isWearingMask = true;
            maskUpTime.start();
            this->noOfMasks--;
            
        }
        else
        {
            Mix_PlayChannel( -1, this->gMissing, 0 );
        }
        
    }
    else if (selectedOption == 3)
    {
        // sanitizer up
        
        if (this->noOfSanitizer >= 1)
        {
            if (player.isSanitized == false)
                this->score += 15;          // only increase score if player was not sanitized but use resources if button pressed extra times
            
            player.isSanitized = true;
            sanitizerUpTime.start();
            this->noOfSanitizer--;
            
        }
        else
        {
            Mix_PlayChannel( -1, this->gMissing, 0 );
        }
        
    }
        
    cout << "Hello " << selectedOption << endl;
}

void GameScreen::endGame()
{
    this->time.stop();
    this->money = 450;
    this->score = 0;
    this->noOfMasks = 0;
    this->noOfSanitizer = 0;
    this->player.current_movement = 0;
    this->player.flag = false;
    this->player.frame = 0;
    this->player.Orientation = SDL_FLIP_NONE;

    maskUpTime.stop();
    sanitizerUpTime.stop();
    player.isSanitized = false;
    player.isWearingMask = false;
}