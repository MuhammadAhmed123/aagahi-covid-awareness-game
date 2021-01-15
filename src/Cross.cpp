#include <iostream>
using namespace std;

#include "Cross.hpp"

Cross::Cross() : Entity()
{

}

Cross::Cross(LTexture* tex, SDL_Rect src, SDL_Rect dst) : Entity(tex, src, dst)
{
    gSpriteClipsbutton[ 0 ] = {0,0,CROSS_WIDTH,CROSS_HEIGHT};
    gSpriteClipsbutton[ 1 ] = {0,60,CROSS_WIDTH,CROSS_HEIGHT};
    gSpriteClipsbutton[ 2 ] = {0,120,CROSS_WIDTH,CROSS_HEIGHT};
    gSpriteClipsbutton[ 3 ] = {0,120,CROSS_WIDTH,CROSS_HEIGHT};

    this->srcRect = gSpriteClipsbutton[ mCurrentSprite ];
}

void Cross::renderCross( SDL_Renderer* gRenderer)
{
    srcRect = gSpriteClipsbutton[ mCurrentSprite ];

    texture->render( dstRect.x, dstRect.y, &srcRect, 0.0, NULL,  SDL_FLIP_NONE, gRenderer, 1,&dstRect);
}


bool Cross::handleEvent( SDL_Event* e, Entity* player )
{
    bool isClicked = false;
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = false;

        if ( (x > dstRect.x) && (x < dstRect.x + CROSS_WIDTH) && (y > dstRect.y) && (y < dstRect.y + CROSS_HEIGHT) )
        {
            inside = true;
			
        }

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = CROSS_SPRITE_MOUSE_OUT;
			this->playedMusic = 0;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = CROSS_SPRITE_MOUSE_OVER_MOTION;
					if (! playedMusic )
                    	Mix_PlayChannel( -1, this->gButtonHover, 0 );
					this->playedMusic = 1;
                    break;
			
				case SDL_MOUSEBUTTONDOWN:
				    mCurrentSprite = CROSS_SPRITE_MOUSE_DOWN;
                    Mix_PlayChannel( -1, this->gButtonClick, 0 );

                    isClicked = true;

					if(x>=dstRect.x && x<=(dstRect.x+CROSS_WIDTH) && y>=dstRect.y && y<(dstRect.y+CROSS_HEIGHT)){
						if(x > player->current_movement){
							player->flag=true;
							player->movement_todo= x - player->current_movement;
							player->final_movement=x;
						}
						else if (x < player->current_movement){
							player->flag=true;
							player->movement_todo= x - player->current_movement;
							player->final_movement=x;
						}
					}
                    break;

				case SDL_MOUSEBUTTONUP:
                    mCurrentSprite = CROSS_SPRITE_MOUSE_UP;
                    break;
			}
		}
	}

    return isClicked;
}
