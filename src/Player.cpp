#include <iostream>
using namespace std;

#include "Player.hpp"

Player::Player() : Entity()
{
    isWearingMask = false;
    isSanitized = false;
    isStandingOnMark = false;
}

Player::Player(LTexture* tex, SDL_Rect src, SDL_Rect dst) : Entity(tex, src, dst)
{
    isWearingMask = false;
    isSanitized = false;
    isStandingOnMark = false;

    gSpriteClips[ 0 ].x = 21;
    gSpriteClips[ 0 ].y =  21;
    gSpriteClips[ 0 ].w =  53;
    gSpriteClips[ 0 ].h = 197;
    //Set sprite clips

    gSpriteClips[ 1 ].x =  77;
    gSpriteClips[ 1 ].y =   21;
    gSpriteClips[ 1 ].w =  54;
    gSpriteClips[ 1 ].h = 197;
    
    gSpriteClips[ 2 ].x = 136;
    gSpriteClips[ 2 ].y =   21;
    gSpriteClips[ 2 ].w =  66;
    gSpriteClips[ 2 ].h = 197;

    gSpriteClips[ 3 ].x =   208;
    gSpriteClips[ 3 ].y =   21;
    gSpriteClips[ 3 ].w =  77;
    gSpriteClips[ 3 ].h = 197;

    gSpriteClips[ 4 ].x =  285;
    gSpriteClips[ 4 ].y =   21;
    gSpriteClips[ 4 ].w =  89;
    gSpriteClips[ 4 ].h = 197;
        
    gSpriteClips[ 5 ].x = 376;
    gSpriteClips[ 5 ].y =   21;
    gSpriteClips[ 5 ].w =  121;
    gSpriteClips[ 5 ].h = 197;

    gSpriteClips[ 6 ].x =   501;
    gSpriteClips[ 6 ].y =   21;
    gSpriteClips[ 6 ].w =  101;
    gSpriteClips[ 6 ].h = 197;

    gSpriteClips[ 7 ].x =  617;
    gSpriteClips[ 7 ].y =   21;
    gSpriteClips[ 7 ].w =  87;
    gSpriteClips[ 7 ].h = 197;
    
    gSpriteClips[ 8 ].x = 711;
    gSpriteClips[ 8 ].y =   21;
    gSpriteClips[ 8 ].w =  66;
    gSpriteClips[ 8 ].h = 197;

    // gSpriteClips[ 9 ].x = 21;
    // gSpriteClips[ 9 ].y =   21;
    // gSpriteClips[ 9 ].w =  53;
    // gSpriteClips[ 9 ].h = 197;

    this->srcRect = this->gSpriteClips[ 0 ];
    this->dstRect = {current_movement, 450, srcRect.w, srcRect.h};
}

void Player::renderPlayer( SDL_Renderer* gRenderer)
{
    SDL_Rect currentClip = gSpriteClips[ frame / WALKING_ANIMATION_FRAMES ];
				
    if ( (current_movement !=final_movement) && (flag==true) ){

        if (movement_todo<0){
            Orientation = SDL_FLIP_HORIZONTAL;                       
            current_movement-=1;

            if(final_movement == current_movement){
                movement_todo = 0;
                flag=false;
                // currentClip->x = 21;
                // currentClip->y = 21;
                // currentClip->w = 53;
                // currentClip->h = 197;
                currentClip = this->gSpriteClips[ 0 ];
            }

        }
        else if (movement_todo>0){
            Orientation = SDL_FLIP_NONE;    
            current_movement+=1;

            if(final_movement==current_movement){
                movement_todo=0;
                flag=false;
                // currentClip->x = 21;
                // currentClip->y = 21;
                // currentClip->w = 53;
                // currentClip->h = 197;
                currentClip = this->gSpriteClips[ 0 ];
            }
        }
        
    }
    else if ( (current_movement == final_movement) && (flag==true) ){
            movement_todo=0;
            flag=false;
            // currentClip->x = 21;
            // currentClip->y = 21;
            // currentClip->w = 53;
            // currentClip->h = 197;
            currentClip = this->gSpriteClips[ 0 ];
    }

    if (flag == false)
    {
        currentClip = this->gSpriteClips[ 0 ];
    }

    srcRect = {currentClip.x, currentClip.y, currentClip.w, currentClip.h};
    this->dstRect = {current_movement, 450, srcRect.w, srcRect.h};

    if (flag==true){
        frame++;
    }
    
    // Cycle animation
    if( frame / WALKING_ANIMATION_FRAMES >= WALKING_ANIMATION_FRAMES )
    {
        frame = 0;
    }

    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  this->Orientation, gRenderer, 1,&dstRect);
}