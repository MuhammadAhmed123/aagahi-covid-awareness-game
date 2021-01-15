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
#include "MainMenu.hpp"

class ScoreScreen : public Screen
{
    public:
        ScoreScreen();
        
        ScoreScreen(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer);

        vector <Button> buttons;

        void renderScoreScreen(SDL_Renderer* gRenderer);

        void handleEvents(SDL_Event& e, Screen* mainMenu);

        void analyzeOption(Screen* mainMenu);  // this will be called when a button is pressed

        Word scoreWord;

    private:
        // will inherit all things from Screen
        LTexture wordSprite;

        int noOfButtons = 1;

        int selectedOption = -1;        // -1 is for no button pressed

        Word scoreWordLetters;
};