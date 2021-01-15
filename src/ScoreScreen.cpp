#include <iostream>
using namespace std;

#include "ScoreScreen.hpp"

ScoreScreen::ScoreScreen() : Screen()
{
    
}

ScoreScreen::ScoreScreen(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer) : Screen(tex, src, dst, a)
{

    cout << "In ScoreScreen constructor\nLoading word" << endl;
    this->wordSprite.loadFromFile("res/img/wordSprite.png", gRenderer);
    cout << "Loaded word" << endl;

    scoreWordLetters = Word("Your Score", &wordSprite, SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 100);
    scoreWord = Word("0", &wordSprite, SCREEN_WIDTH/2 + 100, SCREEN_HEIGHT/2 - 100);

    buttons.push_back(Button( &wordSprite, "Home", SCREEN_WIDTH/2, 570 ));

}

void ScoreScreen::renderScoreScreen(SDL_Renderer* gRenderer)
{
    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);

    buttons[0].render(gRenderer, true);

    // scoreWord.changeWord( to_string(this->score) );
    
    scoreWordLetters.render(gRenderer);
    scoreWord.render(gRenderer);

}

void ScoreScreen::handleEvents(SDL_Event& e, Screen* mainMenu)
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
                        this->analyzeOption(mainMenu);
                        break;
                    }
                }
            }
        }
    }
}

void ScoreScreen::analyzeOption(Screen* mainMenu)
{
    this->alive = false;

    if (selectedOption == 0)
        mainMenu->setAlive(true);
    cout << "Hello " << selectedOption << endl;
}