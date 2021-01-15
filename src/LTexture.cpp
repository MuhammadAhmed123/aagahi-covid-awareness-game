#include"LTexture.hpp"

LTexture::LTexture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer,int r,int g,int b)
{
    texture = NULL;
    cout << "In LTexture::loadFromFile\nIMG Word loading" << endl;
    texture = IMG_LoadTexture(gRenderer, path.c_str());
    cout << "IMG Word loaded" << endl;

    if (texture == NULL)
        cout << "loadTexture failed to load texture. SDL_Error: " << IMG_GetError() << endl;

    //Return success
    cout << "Above texture != NULL" << endl;
    return texture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( texture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( texture, alpha );
}

int LTexture::getWidth()
{
    return width;
}

int LTexture::getHeight()
{
    return height;
}

void LTexture::render( int x, int y, SDL_Rect* srcRect, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer, float scale, SDL_Rect* dstRect)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, int(width*scale), int(height*scale) };
    if (dstRect == NULL)
    {
        //Set clip rendering dimensions
        if( srcRect != NULL )
        {
            renderQuad.w = srcRect->w*scale;
            renderQuad.h = srcRect->h*scale;
        }
    }
    else
    {
        renderQuad = {x,y,dstRect->w,dstRect->h};
    }
    //Render to screen
    SDL_RenderCopyEx( gRenderer, texture, srcRect, &renderQuad, angle, center, flip );
}


// int SDL_RenderCopyEx(SDL_Renderer*          renderer,
//                      SDL_Texture*           texture,
//                      const SDL_Rect*        srcrect,
//                      const SDL_Rect*        dstrect,
//                      const double           angle,
//                      const SDL_Point*       center,
//                      const SDL_RendererFlip flip)
