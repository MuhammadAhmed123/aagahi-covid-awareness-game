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
#include "LTexture.hpp"
#include "Splash.hpp"
#include "Word.hpp"
#include "Button.hpp"
#include "Screen.hpp"
#include "MainMenu.hpp"
#include "Credits.hpp"
#include "GameScreen.hpp"
#include "LTimer.hpp"
#include "Mask.hpp"
#include "Sanitizer.hpp"
#include "Shop.hpp"
#include "ScoreScreen.hpp"
#include "Person.hpp"


class Game
{
    public:
        Game();
        bool init();
        void close();

    private:

        SDL_Rect screenSrcDstRect = {0,0,1248,702};     // all screen sprite have same srcRect

        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;

        Uint8 opacitySplashScreen = 0;
		int fadeWhichSplashScreen = 0;		// 0 for fade in and 1 for fade out

        Splash splashScreen;
        MainMenu mainMenu;
        Credits creditsScreen;
        GameScreen gameScreen;
        Shop shopScreen;
        ScoreScreen scoreScreen;

        LTexture splashTexture;
        LTexture mainMenuTexture;
        LTexture creditsTexture;
        LTexture gameScreenTexture;
        LTexture shopTexture;
        LTexture wordSprite;
        LTexture scoreTexture;
        LTexture walkingBoyTexture;
        LTexture walkingGirlTexture;
        LTexture chaiWalaTexture;

        bool gameRunning;

};