#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

#include "Entity.hpp"
#include "Screen.hpp"
#include "LTexture.hpp"
#include "Button.hpp"
#include "MainMenu.hpp"
#include "LTimer.hpp"
#include "Mask.hpp"
#include "Sanitizer.hpp"
#include "Cross.hpp"
#include "Player.hpp"
#include "LTimer.hpp"

class GameScreen : public Screen
{
    public:
        GameScreen();
        
        GameScreen(LTexture* tex,SDL_Rect src, SDL_Rect dst, bool a, SDL_Renderer* gRenderer);

        vector <Button> buttons;

        void renderGameScreen(SDL_Renderer* gRenderer);

        void handleEvents(SDL_Event& e, Screen* mainMenu, Screen* shop);

        void analyzeOption(Screen* mainMenu, Screen* shop);  // this will be called when a button is pressed

        void endGame();

        // score, time and timeWord will be inherited from Screen
        Word noOfMasksWord;
        Word noOfSanitizerWord;
        Word moneyWord;

        Player player;      // public because to be accessed by Game class

        LTimer maskUpTime;
        LTimer sanitizerUpTime;
        

    private:
        // will inherit all things from Screen
        LTexture wordSprite;

        // LTexture backSprite;
        Word scoreWordLetters;
        Word scoreWord;
        Word timeWordLetters;

        Word maskWarn;
        Word sanitizerWarn;
        Word standWarn;

        int noOfButtons = 4;

        LTexture maskTexture;
        LTexture sanitizerTexture;
        LTexture crossTexture;
        LTexture playerTexture;
        LTexture playerMaskedTexture;
        LTexture moneyTexture;
        LTexture warningBorder;

        Entity moneyPicture;

        Mask mask;
        Sanitizer sanitizer;

        Word maskUpTimeWord;
        Word sanitizerUpTimeWord;

        vector <Cross> crosses;
        const int TOTAL_CROSSES = 4;

        int selectedOption = -1;        // -1 is for no button pressed

};