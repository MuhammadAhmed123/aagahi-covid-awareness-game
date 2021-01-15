#include <iostream>
using namespace std;

#include "Person.hpp"

Person::Person() : Entity()
{

}

Person::Person(LTexture* tex, SDL_Rect src, SDL_Rect dst, TYPE type) : Entity(tex, src, dst)
{
    if (type == TYPE_CHAI_WALA)
    {
        this->type = TYPE_CHAI_WALA;
        current_movement = 160;
        WALKING_ANIMATION_FRAMES = 10;

        SDL_Rect r1 = {1, 0, 66, 183};
        SDL_Rect r2 = {74, 0, 66, 183};
        SDL_Rect r3 = {147, 0, 69, 183};
        SDL_Rect r4 = {217, 0, 72, 183};
        SDL_Rect r5 = {292, 0, 72, 183};
        SDL_Rect r6 = {366, 0, 72, 183};
        SDL_Rect r7 = {441, 0, 71, 183};
        SDL_Rect r8 = {520, 0, 67, 183};
        SDL_Rect r9 = {598, 0, 62, 183};
        SDL_Rect r10 = {674, 0, 62, 183};
        
        gSpriteClips.push_back(r1);
        gSpriteClips.push_back(r2);
        gSpriteClips.push_back(r3);
        gSpriteClips.push_back(r4);
        gSpriteClips.push_back(r5);
        gSpriteClips.push_back(r6);
        gSpriteClips.push_back(r7);
        gSpriteClips.push_back(r8);
        gSpriteClips.push_back(r9);
        gSpriteClips.push_back(r10);

        this->srcRect = gSpriteClips[ 0 ];
        this->dstRect = {current_movement, 450, srcRect.w - 10, srcRect.h - 20};
    }
    else if (type == TYPE_WALKING_BOY)
    {
        this->type = TYPE_WALKING_BOY;
        current_movement = 340;
        WALKING_ANIMATION_FRAMES = 7;

        SDL_Rect r1 = {40, 21, 32, 169};
        SDL_Rect r2 = {86, 21, 47, 169};
        SDL_Rect r3 = {214, 21, 62, 169};
        SDL_Rect r4 = {366, 21, 102, 169};
        SDL_Rect r5 = {476, 21, 94, 169};
        SDL_Rect r6 = {591, 21, 79, 169};
        SDL_Rect r7 = {696, 21, 67, 169};

        gSpriteClips.push_back(r1);
        gSpriteClips.push_back(r2);
        gSpriteClips.push_back(r3);
        gSpriteClips.push_back(r4);
        gSpriteClips.push_back(r5);
        gSpriteClips.push_back(r6);
        gSpriteClips.push_back(r7);

        this->srcRect = gSpriteClips[ 0 ];
        this->dstRect = {current_movement, 450, srcRect.w, srcRect.h};

    }
    else if (type == TYPE_WALKING_GIRL)
    {
        this->type = TYPE_WALKING_GIRL;
        current_movement = 670;
        WALKING_ANIMATION_FRAMES = 8;

        SDL_Rect r1 = {35, 32, 83, 225};
        SDL_Rect r2 = {199, 32, 83, 225};
        SDL_Rect r3 = {532, 32, 83, 225};
        SDL_Rect r4 = {532, 32, 83, 225};
        SDL_Rect r5 = {696, 32, 83, 225};
        SDL_Rect r6 = {862, 32, 83, 225};
        SDL_Rect r7 = {1023, 32, 83, 225};
        SDL_Rect r8 = {1186, 32, 83, 225};

        gSpriteClips.push_back(r1);
        gSpriteClips.push_back(r2);
        gSpriteClips.push_back(r3);
        gSpriteClips.push_back(r4);
        gSpriteClips.push_back(r5);
        gSpriteClips.push_back(r6);
        gSpriteClips.push_back(r7);
        gSpriteClips.push_back(r8);

        this->srcRect = gSpriteClips[ 0 ];
        this->dstRect = {410, 450, srcRect.w - 15, srcRect.h - 45};
    }

}

void Person::renderPerson( SDL_Renderer* gRenderer)
{
    SDL_Rect* currentClip = &gSpriteClips[ frame / WALKING_ANIMATION_FRAMES ];

    if (this->type == TYPE_WALKING_BOY)
    {
        if(current_movement < 1240 && reverse==false){
            current_movement+=1;
            Orientation = SDL_FLIP_NONE;
        }
        else if (current_movement >= 1240 && reverse==false){
            reverse=true;
            Orientation = SDL_FLIP_HORIZONTAL;
            current_movement-=1;
        }
        else if (current_movement > 0 && reverse==true){    //Walking public person animation
            current_movement-=1;
            Orientation = SDL_FLIP_HORIZONTAL;
        }
        else if (current_movement == 0 && reverse==true){
            Orientation = SDL_FLIP_NONE;
            reverse = false;
        }
    }
    
	if (this->type == TYPE_WALKING_GIRL)
    {
        if(current_movement < 1240 && reverse==false){
            current_movement+=1;
            Orientation = SDL_FLIP_HORIZONTAL;
        }
        else if (current_movement >= 1240 && reverse==false){
            reverse=true;
            Orientation = SDL_FLIP_NONE;
            current_movement-=1;
        }
        else if (current_movement > 0 && reverse==true){    //Walking public person animation
            current_movement-=1;
            Orientation = SDL_FLIP_NONE;
        }
        else if (current_movement == 0 && reverse==true){
            Orientation = SDL_FLIP_HORIZONTAL;
            reverse = false;
        }
    }

    srcRect = {currentClip->x, currentClip->y, currentClip->w, currentClip->h};

    if ( this->type == TYPE_CHAI_WALA )
        this->dstRect = {current_movement, 420, srcRect.w - 10, srcRect.h - 20};
    else if (this->type == TYPE_WALKING_BOY )
        this->dstRect = {current_movement, 450, srcRect.w, srcRect.h};
    else if (this->type == TYPE_WALKING_GIRL )
        this->dstRect = {current_movement, 470, srcRect.w - 15, srcRect.h - 30};

    ++frame;
    
    // Cycle animation
    if( frame / WALKING_ANIMATION_FRAMES >= WALKING_ANIMATION_FRAMES )
    {
        frame = 0;
    }

    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  this->Orientation, gRenderer, 1,&dstRect);
}