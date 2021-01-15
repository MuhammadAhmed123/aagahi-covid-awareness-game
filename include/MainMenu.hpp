#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

#include "Screen.hpp"
#include "LTexture.hpp"
#include "Button.hpp"
#include "Credits.hpp"
#include "GameScreen.hpp"

class MainMenu : public Screen
{
    public:
        MainMenu();
        
        MainMenu(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer);

        vector <Button> buttons;

        void renderMainMenu(SDL_Renderer* gRenderer);

        void handleEvents(SDL_Event& e, bool& gameRunning, Screen* creditsScreen, Screen* gameScreen);

        void analyzeOption(bool& gameRunning, Screen* creditsScreen, Screen* gameScreen);       // this will be called when a button is pressed

    private:
        // will inherit all things from Screen
        LTexture wordSprite;

        int noOfButtons = 3;

        int selectedOption = -1;        // -1 is for no button pressed
        
};