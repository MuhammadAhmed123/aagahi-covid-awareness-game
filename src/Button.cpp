#include <iostream>
#include "Button.hpp"
using namespace std;

Button::Button(LTexture* Texture, string str, int x, int y)
{
    this->word = new Word(str, Texture, x, y);
    this->btnTexture = Texture;
    // for (int i = 0; i < 3; i++)
    // {
    //     BtnRect[i].x = 88 * (i+1);
    //     BtnRect[i].y = 99 * 5;
    //     BtnRect[i].w = 1500;
    //     BtnRect[i].h = 99;
    // }
    BtnRect[0] = {0, 255, 145, 60};
    BtnRect[1] = {0, 325, 145, 60};
    // BtnRect[2] = {0, 397, 145, 60};

    setPosition(x, y);
}


void Button::setText(string str)
{
   word->setText(str);
    setPosition(x, y);
}

void Button::setPosition(int x, int y)
{
    this ->x = x;
    this ->y = y;
    this->word->setPosition(x + (word->getLength()/2)*88 ,y -99/2);
}

void Button::render(SDL_Renderer* gRenderer, bool small) {

    SDL_Rect srcBtnRect;
    if (this->state == 1)
        srcBtnRect = BtnRect[1];
    else
        srcBtnRect = BtnRect[0];
    
    SDL_Rect dstRect;

    if (small)
    {
        dstRect = {this -> x - ( srcBtnRect.w * 2)/2 , this -> y - 30, srcBtnRect.w * 2, srcBtnRect.h};
    }
    else
    {
        dstRect = {this -> x - ( srcBtnRect.w * 3)/2 , this -> y - 30, srcBtnRect.w * 3, srcBtnRect.h};
    }
    
    btnTexture->render(dstRect.x, dstRect.y, &srcBtnRect, 0.0, NULL, SDL_FLIP_NONE, gRenderer, 1, &dstRect);

    word->render(gRenderer);
    // btnTexture->render(this->x + (word->getLength())/2 * 88, this->y-99/2, &BtnRect[2], 0.0, NULL, SDL_FLIP_NONE, gRenderer, 1, NULL);
    
}

bool Button::cursorOverIt(int mx, int my, bool small)
{
    if (small)
    {
        if ( (mx > this->x - ( BtnRect[1].w * 2)/2) && (mx < this->x - ( BtnRect[1].w * 2)/2 + BtnRect[1].w * 2) )
        {
            if ( (my > this->y - 30) && ( my < this-> y-30 + BtnRect[1].h ) )
            {
                
                return true;
            }
        }
    }
    else
    {
        if ( (mx > this->x - ( BtnRect[1].w * 3)/2) && (mx < this->x - ( BtnRect[1].w * 3)/2 + BtnRect[1].w * 3) )
        {
            if ( (my > this->y - 30) && ( my < this-> y-30 + BtnRect[1].h ) )
            {
                
                return true;
            }
        }
    }
    
    return false;
}