#include <iostream>
using namespace std;

#include "Screen.hpp"

Screen::Screen() : Entity()
{
    this->alive = false;
    
}

Screen::Screen(LTexture* tex, SDL_Rect src, SDL_Rect dst, bool a) : Entity(tex, src, dst)
{
    alive = a;
    
}

Screen::~Screen()
{
    
}

void Screen::setAlive(bool a)
{
    alive = a;
}

bool Screen::getAlive()
{
    return alive;
}