#ifndef Button_hpp
#define Button_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_mixer.h>
#include <string>
#include "Word.hpp"
#include "LTexture.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;

class Button
{
private:
    int x, y;
    SDL_Rect BtnRect[2];
    LTexture* btnTexture;

    //Screen dimension constants 16:9
    const int SCREEN_WIDTH = 1248;
    const int SCREEN_HEIGHT = 702;

public:
    Button(LTexture* Texture, string str, int x, int y);
    void render(SDL_Renderer* gRenderer, bool small);
    void setPosition(int x, int y);
    void setText(string str);
    Word* word;
    bool cursorOverIt(int mx, int my, bool small);

    int state = 0;      // 0 for no hover and 1 for hover
    int playedMusic = 0;        // 0 for not 1 for already played music
};
#endif /* Button_hpp */
