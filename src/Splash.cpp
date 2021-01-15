#include <iostream>
using namespace std;

#include "Splash.hpp"

Splash::Splash() : Screen()
{
    
}

Splash::Splash(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a) : Screen(tex, src, dst, a)
{

}