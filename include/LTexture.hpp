#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <stdio.h>

using namespace std;

//Texture wrapper class
class LTexture
{
private:

    SDL_Texture* texture;

    int width;

    int height;

public:

    LTexture();

    ~LTexture();

    bool loadFromFile( std::string path, SDL_Renderer* gRenderer,int r = 255,int g = 255,int b = 255 );

    void free();    //Deallocates texture

    //Method to set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending method
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation method
    void setAlpha( Uint8 alpha );

    //Rendering method
    void render( int x, int y, SDL_Rect* srcRect = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Renderer* gRenderer = NULL,float scale = 1,SDL_Rect* dstRect = NULL);

    int getWidth();         //returns the width of the texture

    int getHeight();        //returns the height of texture
};


#endif // LTEXTURE_H