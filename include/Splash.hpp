#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#include "Screen.hpp"
#include "LTexture.hpp"

class Splash : public Screen
{
    public:
        Splash();
        
        Splash(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a);
        
    private:
        // will inherit all things from Screen
        
};