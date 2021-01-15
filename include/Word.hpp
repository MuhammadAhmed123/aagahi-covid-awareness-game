#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
#include "LTexture.hpp"
#include "Character.hpp"

using namespace std;

class Word
{
private:
    Point position; //position of word
    string text; //text of the word
    int wordLen;  //length of the word
    int width;   //width of the word
    int height; //height of the word
    LTexture* spriteSheetTexture;
    Character* chars; //pointer of character class(used for creating dynamic array of Characters)

public:
    Word();
    Word(string text, LTexture* image, float x, float y);
    ~Word();
    void render(SDL_Renderer*); //to draw the word on screen
    int getLength();
    int getWidth();
    void changeWord(string);  //changes the text of the Word
    void operator = (const Word&); //operating overloading for assignment operator.
    string getText() {return text;} //used to get text of the word
    void setText(string t) {text = t;}
    void setPosition(int x, int y) {position.x = x; position.y = y;}
};
