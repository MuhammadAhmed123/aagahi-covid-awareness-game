#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "LTexture.hpp"
#include "Entity.hpp"

using namespace std;

enum TYPE
{
    TYPE_CHAI_WALA = 0,
    TYPE_WALKING_BOY = 1,
    TYPE_WALKING_GIRL = 2
};

class Person : public Entity
{
    public:

        Person();
        Person(LTexture* tex, SDL_Rect src, SDL_Rect dst, TYPE type);

        void renderPerson(SDL_Renderer* gRenderer);

        int WALKING_ANIMATION_FRAMES;

        vector <SDL_Rect> gSpriteClips;
        
    private:

        int mCurrentSprite = 0;

        // in this class, srcRect will be equivalent to currentClip SDL_Rect

        bool reverse = false;

        TYPE type;

        // current_movement, frame and orientation will be inherited from Entity

    
};