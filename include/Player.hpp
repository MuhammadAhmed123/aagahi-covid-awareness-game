#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <stdio.h>

#include "LTexture.hpp"
#include "Entity.hpp"

using namespace std;

class Player : public Entity
{
    private:

        int mCurrentSprite = 0;

        // in this class, srcRect will be equivalent to currentClip SDL_Rect

    public:

        Player();
        Player(LTexture* tex, SDL_Rect src, SDL_Rect dst);
        
        void renderPlayer(SDL_Renderer* gRenderer);

        // bool handleEvent( SDL_Event* e );       // this returns whether this Player has been clicked or not

        int WALKING_ANIMATION_FRAMES = 9;

        SDL_Rect gSpriteClips[ 9 ];

        // will inherit isWearingMask, isSanitized and isStandingOnMark from Entity
        
};