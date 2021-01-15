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

class Cross : public Entity
{
    public:
        Cross();
        Cross(LTexture* tex, SDL_Rect src, SDL_Rect dst);
        
        void renderCross(SDL_Renderer* gRenderer);

        enum crossSprite
        {
            CROSS_SPRITE_MOUSE_OUT = 0,
            CROSS_SPRITE_MOUSE_OVER_MOTION = 2,
            CROSS_SPRITE_MOUSE_DOWN = 1,
            CROSS_SPRITE_MOUSE_UP = 3,
            CROSS_SPRITE_TOTAL = 4
        };

        bool handleEvent( SDL_Event* e, Entity* player );       // this returns whether this cross has been clicked or not

        int playedMusic = 0;


    private:
        const int CROSS_WIDTH = 60;
        const int CROSS_HEIGHT = 60;

        int mCurrentSprite = CROSS_SPRITE_MOUSE_OUT;
        SDL_Rect gSpriteClipsbutton[ CROSS_SPRITE_TOTAL ];

        // in this class, srcRect will be equivalent to currentClip SDL_Rect
        
};