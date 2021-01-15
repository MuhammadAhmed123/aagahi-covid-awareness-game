#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "LTexture.hpp"
#include <stdio.h>

using namespace std;

class Entity
{
    public:
        Entity();
        Entity(LTexture* tex, SDL_Rect src, SDL_Rect dst);
        ~Entity();
        SDL_Rect getSrcRect();
        SDL_Rect getDstRect();
        LTexture* getTexture();
        void setTexture(LTexture* tex);
        void render(SDL_Renderer* gRenderer);
        void operator = (const Entity&); //operating overloading for assignment operator.

        // bewlow vars will be used by Cross class and are only for Player class

        int current_movement=0; // This is the current x-coord movement of the person 
        int movement_todo=0;    // This is the movement which needs to be done to the person
        int final_movement=0;
        bool flag= false;
        int frame = 0;
        SDL_RendererFlip Orientation = SDL_FLIP_NONE;

        int maskPrice;      // only to be used by Mask class

        int sanitizerPrice;     // only to be used by Sanitizer class

        Mix_Chunk *gButtonHover = NULL;
        Mix_Chunk *gButtonClick = NULL;
        Mix_Chunk *gMissing = NULL;

        // below bools to be used by Player class only
        bool isWearingMask;
        bool isSanitized;
        bool isStandingOnMark;


    protected:
        LTexture* texture;
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        
};