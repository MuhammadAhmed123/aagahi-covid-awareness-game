#include <iostream>
using namespace std;

#include "Entity.hpp"

Entity::Entity()
{
    texture = NULL;
    srcRect = {0,0,0,0};
    dstRect = {0,0,0,0};

    gButtonHover = Mix_LoadWAV( "res/music/button_hover.wav" );
    gButtonClick = Mix_LoadWAV( "res/music/button_click.wav" );

    gButtonHover = Mix_LoadWAV( "res/music/button_hover.wav" );
    if( gButtonHover == NULL )
    {
        printf( "Failed to load gButtonHover sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        
    }

    gButtonClick = Mix_LoadWAV( "res/music/button_click.wav" );
    if( gButtonClick == NULL )
    {
        printf( "Failed to load gButtonClick sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        
    }

    gMissing = Mix_LoadWAV( "res/music/missing.wav" );
    if( gButtonClick == NULL )
    {
        printf( "Failed to load gMissing sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        
    }
}

Entity::~Entity()
{
    // Mix_FreeChunk( gButtonHover );
    // gButtonHover = NULL;
    // Mix_FreeChunk( gButtonClick );
    // gButtonClick = NULL;
    // Mix_FreeChunk( gMissing );
    // gMissing = NULL;
}

void Entity::setTexture(LTexture* tex)
{
    // delete texture;
    texture = NULL;
    texture = tex;
}

Entity::Entity(LTexture* tex, SDL_Rect src, SDL_Rect dst) : Entity()
{
    texture = tex;
    srcRect = src;
    dstRect = dst;
}

SDL_Rect Entity::getSrcRect()
{
    return srcRect;
}

SDL_Rect Entity::getDstRect()
{
    return dstRect;
}

LTexture* Entity::getTexture()
{
    return texture;
}

void Entity::render( SDL_Renderer* gRenderer)
{
    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);
}

void Entity::operator = (const Entity& cpy)
{
    delete texture;
    texture = NULL;
    this->texture = cpy.texture;
    this->srcRect = cpy.srcRect;
    this->dstRect = cpy.dstRect;
}