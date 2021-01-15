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
#include "GameScreen.hpp"
#include "LTimer.hpp"
#include "Mask.hpp"
#include "Sanitizer.hpp"

class Shop : public Screen
{
    public:
        Shop();
        
        Shop(LTexture* tex,SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer);

        vector <Button> buttons;

        void renderShop(SDL_Renderer* gRenderer, Screen* gameScreen);

        void handleEvents(SDL_Event& e, Screen* gameScreen);

        void analyzeOption(Screen* gameScreen);  // this will be called when a button is pressed

        Word noOfMasksWord;
        Word noOfSanitizerWord;

        Word moneyWord;

    private:
        // will inherit all things from Screen
        LTexture wordSprite;

        LTexture moneyTexture;

        Entity moneyPicture;

        int noOfButtons = 3;

        LTexture maskTexture;
        LTexture sanitizerTexture;

        Mask mask;
        Sanitizer sanitizer;

        Mask maskBig;
        Sanitizer sanitizerBig;

        int selectedOption = -1;        // -1 is for no button pressed
};