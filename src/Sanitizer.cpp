#include <iostream>
using namespace std;

#include "Sanitizer.hpp"

Sanitizer::Sanitizer() : Entity()
{

}

Sanitizer::Sanitizer(LTexture* tex, SDL_Rect src, SDL_Rect dst) : Entity(tex, src, dst)
{
    sanitizerPrice = 150;
}

void Sanitizer::renderSanitizer( SDL_Renderer* gRenderer)
{
    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);
}