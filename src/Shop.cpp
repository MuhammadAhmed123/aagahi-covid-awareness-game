#include <iostream>
using namespace std;

#include "Shop.hpp"

Shop::Shop() : Screen()
{
    
}

Shop::Shop(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer) : Screen(tex, src, dst, a)
{
    cout << "In Shop constructor\nLoading word" << endl;
    this->wordSprite.loadFromFile("res/img/wordSprite.png", gRenderer);
    cout << "Loaded word" << endl;

    buttons.push_back(Button( &wordSprite, "Back", SCREEN_WIDTH/2, SCREEN_HEIGHT - 80 ));
    buttons.push_back(Button( &wordSprite, "Buy", SCREEN_WIDTH/2 + 300, SCREEN_HEIGHT/2 - 130));
    buttons.push_back(Button( &wordSprite, "Buy", SCREEN_WIDTH/2 + 300, SCREEN_HEIGHT/2 + 100 ));

    maskTexture.loadFromFile("res/img/mask_single.png", gRenderer);
    SDL_Rect maskSrcRect = {0,0,396,274};
    SDL_Rect maskDstRect = {SCREEN_WIDTH/2 - 70,10,60,50};
    mask = Mask(&maskTexture, maskSrcRect, maskDstRect);

    sanitizerTexture.loadFromFile("res/img/sanitizer.png", gRenderer);
    SDL_Rect sanitizerSrcRect = {0,0,200,373};
    SDL_Rect sanitizerDstRect = {SCREEN_WIDTH/2 - 60,70,40,60};
    sanitizer = Sanitizer(&sanitizerTexture, sanitizerSrcRect, sanitizerDstRect);

    noOfMasksWord = Word("0", &wordSprite, SCREEN_WIDTH/2 + 40, 37);
    noOfSanitizerWord = Word("0", &wordSprite, SCREEN_WIDTH/2 + 40, 101);

    SDL_Rect maskDstRectBig = {300,SCREEN_WIDTH/2 - 480,200,150};
    maskBig = Mask(&maskTexture, maskSrcRect, maskDstRectBig);

    SDL_Rect sanitizerDstRectBig = {330,SCREEN_WIDTH/2 - 300,125,200};
    sanitizerBig = Sanitizer(&sanitizerTexture, sanitizerSrcRect, sanitizerDstRectBig);

    SDL_Rect moneySrc = {0,0, 394, 430};
    SDL_Rect moneyDst = {80, 20, 90, 97};
    moneyTexture.loadFromFile("res/img/money.png", gRenderer);
    moneyPicture = Entity(&moneyTexture, moneySrc, moneyDst);
    moneyWord = Word("0", &wordSprite, 220 , 67);
}

void Shop::renderShop(SDL_Renderer* gRenderer, Screen* gameScreen)
{
    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);

    buttons[0].render(gRenderer, true);
    buttons[1].render(gRenderer, false);
    buttons[2].render(gRenderer, false);

    mask.renderMask(gRenderer);
    sanitizer.renderSanitizer(gRenderer);

    maskBig.renderMask(gRenderer);
    sanitizerBig.renderSanitizer(gRenderer);

    noOfMasksWord.render(gRenderer);
    noOfSanitizerWord.render(gRenderer);

    string tempMoneyWord = to_string(gameScreen->money);
    moneyWord.changeWord(tempMoneyWord);

    moneyPicture.render(gRenderer);
    moneyWord.render(gRenderer);
}

void Shop::handleEvents(SDL_Event& e, Screen* gameScreen)
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

                        if ( (i == 1) && (gameScreen->money < 20) )
                        {
                            Mix_PlayChannel( -1, this->gMissing, 0 );
                        }
                        else if ( (i == 2) && (gameScreen->money < 150) )
                        {
                            Mix_PlayChannel( -1, this->gMissing, 0 );
                        }
                        else
                        {
                            Mix_PlayChannel( -1, this->gButtonClick, 0 );
                        }

                        this->analyzeOption(gameScreen);
                        break;
                    }
                }
            }
        }
    }
}

void Shop::analyzeOption(Screen* gameScreen)
{
    
    if (selectedOption == 0)
    {
        this->alive = false;
        gameScreen->setAlive(true);
    }
    else if (selectedOption == 1)
    {
        if (gameScreen->money >= 20)
        {
            gameScreen->noOfMasks++;
            gameScreen->money -= 20;
        }
    }
    else if (selectedOption == 2)
    {
        if (gameScreen->money >= 150)
        {
            gameScreen->noOfSanitizer++;
            gameScreen->money -= 150;
        }
    }

    cout << "Hello " << selectedOption << endl;
}