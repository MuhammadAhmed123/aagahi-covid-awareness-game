#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include"LTexture.hpp"
#ifndef POINT_H
#define POINT_H
#include <iostream>
//#pragma once

struct Point
{
	int x;
	int y;

	Point()
	{
        x = 0;
        y = 0;
	}

	Point(int x, int y)
	{
	    this->x = x;
	    this->y = y;
	}
	Point(const Point& point)
	{
	    x = point.x;
	    y = point.y;
	}
	bool operator == (Point point) //equal to operator
	{
	    return (this->x == point.x && this->y == point.y);
	}
	void operator = (Point point) //assignment operator
	{
	    this->x = point.x;
	    this->y = point.y;
	}
	bool operator != (Point point) //not equal operator
	{
	    return (this->x != point.x || this->y != point.y);
	}
	Point operator /(int divisor) //used to divide both x and y by a number
	{
	    Point p;
	    p.x = y/divisor;
	    p.y = x/divisor;
	    return p;
	}
	Point operator + (int number) //adds a number to both x and y
	{
	    x += number;
	    y += number;
	    return *this;
	}
	Point operator - (int number) //subtracts a number from both x and y
	{
	    x -= number;
	    y -= number;
	    return *this;
	}
};
#endif // POINT_H


class Character
{
private:
    Point position; //Position of the Character
    int character_value = 0; //ascii value of the Character
    int width; //width of character
    int height; //height of character
    SDL_Rect spriteClips; //clip specific to the Character
    LTexture* spriteSheetTexture; //font image
	
public:
    Character();
    Character(LTexture* image, float x, float y, int ascii);
    ~Character();
    void Render(SDL_Renderer* gRenderer, bool debug);
    void operator = (const Character& cpy); //operator overloading for assignment operatot
};

