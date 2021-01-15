#include <iostream>
using namespace std;

#include "Mask.hpp"

Mask::Mask() : Entity()
{

}

Mask::Mask(LTexture* tex, SDL_Rect src, SDL_Rect dst) : Entity(tex, src, dst)
{
    maskPrice = 20;

}

void Mask::renderMask( SDL_Renderer* gRenderer)
{
    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);
}