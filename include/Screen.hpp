#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#include "Entity.hpp"
#include "LTexture.hpp"
#include "LTimer.hpp"
#include "Word.hpp"

class Screen : public Entity
{
    public:
        Screen();
        ~Screen();
        Screen(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a);
        void setAlive(bool a);
        bool getAlive();

        LTimer time;    // only to be used in Game Screen

        Word timeWord;      // only to be used in Game Screen

        int score;      // only to be used in Game Screen

        // below are used only in Game Screen
        int noOfMasks = 0;
        int noOfSanitizer = 0;
        
        int money = 0;   

    protected:
        // will inherit all things from Entity
        bool alive;

        const int SCREEN_WIDTH = 1248;
        const int SCREEN_HEIGHT = 702;       
};