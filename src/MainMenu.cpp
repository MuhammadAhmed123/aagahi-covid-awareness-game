#include <iostream>
using namespace std;

#include "MainMenu.hpp"

MainMenu::MainMenu() : Screen()
{
    
}

MainMenu::MainMenu(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer) : Screen(tex, src, dst, a)
{
    cout << "In main constructor\nLoading word" << endl;
    this->wordSprite.loadFromFile("res/img/wordSprite.png", gRenderer);
    cout << "Loaded word" << endl;

    buttons.push_back(Button( &wordSprite, "Play", SCREEN_WIDTH/2, 400 ));
    buttons.push_back(Button( &wordSprite, "Credits", SCREEN_WIDTH/2, 500 ));
    buttons.push_back(Button( &wordSprite, "Quit", SCREEN_WIDTH/2, 600 ));

}

void MainMenu::renderMainMenu(SDL_Renderer* gRenderer)
{
    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);

    buttons[0].render(gRenderer, false);
    buttons[1].render(gRenderer, false);
    buttons[2].render(gRenderer, false);
}

void MainMenu::handleEvents(SDL_Event& e, bool& gameRunning, Screen* creditsScreen, Screen* gameScreen)
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
                    if (buttons[i].cursorOverIt(x,y, false))
                    {  
                        this->selectedOption = i;
                        Mix_PlayChannel( -1, this->gButtonClick, 0 );
                        this->analyzeOption(gameRunning, creditsScreen, gameScreen);
                        break;
                    }
                }
            }
        }
    }
}

void MainMenu::analyzeOption(bool& gameRunning, Screen* creditsScreen, Screen* gameScreen)
{
    this->alive = false;

    if (selectedOption == 2)
        gameRunning = false;
    if (selectedOption == 1)
        creditsScreen->setAlive(true);
    if (selectedOption == 0)
    {
        gameScreen->setAlive(true);
        gameScreen->time.start();
    }
    
    cout << "analyzeOption " << selectedOption << endl;
}