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

class Sanitizer : public Entity
{
    public:
        Sanitizer();
        Sanitizer(LTexture* tex, SDL_Rect src, SDL_Rect dst);
        
        void renderSanitizer(SDL_Renderer* gRenderer);

        int timeEffective = 25;         // in seconds


    private:
        
};