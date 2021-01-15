#include <iostream>
using namespace std;

#include "Game.hpp"

//Screen dimension constants 16:9
const int SCREEN_WIDTH = 1248;
const int SCREEN_HEIGHT = 702;

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Aagahi Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}
	cout << "Game Init complete " << success << endl; 
	return success;
}

void Game::close()
{
	// //Free loaded images
	// gSpriteSheetTexture.free();
    cout << "Game Ended" << endl;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

Game::Game()
{
    bool init_bool = init();

	if (init_bool == false)
	{
		cout << "Game init function failed" << endl;
	}
	else
	{
		cout << "Loading media" << endl;
		
		cout << "Loading splash" << endl;
		// below line loads the main texture file which contains most textures	
		if (splashTexture.loadFromFile("res/img/splash.png", gRenderer) == false)	
			cout << "Splash Texture load failed" << endl;
		cout << "Loaded splash" << endl;
		Splash splashScreen(&splashTexture, screenSrcDstRect, screenSrcDstRect, true);

		cout << "Loading main" << endl;
		if (mainMenuTexture.loadFromFile("res/img/mainMenu.png", gRenderer) == false)
			cout << "Main Texture load failed" << endl;
		cout << "Loaded main" << endl;
		MainMenu mainMenu(&mainMenuTexture, screenSrcDstRect, screenSrcDstRect, false, gRenderer);

		creditsTexture.loadFromFile("res/img/credits.png", gRenderer);
		Credits creditsScreen(&creditsTexture, screenSrcDstRect, screenSrcDstRect, false, gRenderer);

		gameScreenTexture.loadFromFile("res/img/road.png", gRenderer);
		GameScreen gameScreen(&gameScreenTexture, screenSrcDstRect, screenSrcDstRect, false, gRenderer);

		shopTexture.loadFromFile("res/img/shop.png", gRenderer);
		Shop shopScreen(&shopTexture, screenSrcDstRect, screenSrcDstRect, false, gRenderer);

		cout << "In GameScreen constructor\nLoading word" << endl;
    	this->wordSprite.loadFromFile("res/img/wordSprite.png", gRenderer);
    	cout << "Loaded word" << endl;

		scoreTexture.loadFromFile("res/img/score.png", gRenderer);
		ScoreScreen scoreScreen(&scoreTexture, screenSrcDstRect, screenSrcDstRect, false, gRenderer);

		SDL_Rect tempRect = {0,0,0,0};		// place holder because hard coded in constructor

		walkingBoyTexture.loadFromFile("res/img/boy_walking.png", gRenderer);
		Person walkingBoy(&walkingBoyTexture, tempRect, tempRect, TYPE_WALKING_BOY);

		walkingGirlTexture.loadFromFile("res/img/girl_walking.png", gRenderer);
		Person walkingGirl(&walkingGirlTexture, tempRect, tempRect, TYPE_WALKING_GIRL);

		chaiWalaTexture.loadFromFile("res/img/chaiwala.png", gRenderer);
		Person chaiWala(&chaiWalaTexture, tempRect, tempRect, TYPE_CHAI_WALA);

		cout << "Loaded media" << endl;

		int tempTime = 0;
		string tempTimeString = ""; // variable used to update timeWord of GameScreen

		// int tempNoOfMasks = 0;
		string tempNoOfMasksString = "";

		// int tempNoOfSanitizer = 0;
		string tempNoOfSanitizerString = "";

		string tempScoreString = "";

		gameRunning = true;

		SDL_Event event;

		while (gameRunning)
		{
			// cout << "In game loop" << endl;

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;

				if (mainMenu.getAlive() == true)
					mainMenu.handleEvents(event, gameRunning, &creditsScreen, &gameScreen);
				
				if (creditsScreen.getAlive() == true)
					creditsScreen.handleEvents(event, &mainMenu);
				
				if (gameScreen.getAlive() == true)
					gameScreen.handleEvents(event, &mainMenu, &shopScreen);
				
				if (shopScreen.getAlive() == true)
					shopScreen.handleEvents(event, &gameScreen);
				
				if (scoreScreen.getAlive() == true)
					scoreScreen.handleEvents(event, &mainMenu);
			}

			if (splashScreen.getAlive() == true)
			{
				if (fadeWhichSplashScreen == 0)
					opacitySplashScreen = opacitySplashScreen + 1;
				else if (fadeWhichSplashScreen == 1)
					opacitySplashScreen = opacitySplashScreen - 1;

				if (opacitySplashScreen == 200)
					fadeWhichSplashScreen = 1;
				if (opacitySplashScreen == 0)
				{
					splashScreen.setAlive(false);
					mainMenu.setAlive(true);
				}
				
				splashTexture.setAlpha(opacitySplashScreen);

				if ( SDL_RenderClear(gRenderer) < 0 )
        			cout << "SDL_RenderClear failed. SDL_Error: " << SDL_GetError() << endl;

				splashScreen.render(gRenderer);

				// SDL_RenderPresent(gRenderer);
			}
			
			if (mainMenu.getAlive() == true)
			{
				if ( SDL_RenderClear(gRenderer) < 0 )
        			cout << "SDL_RenderClear failed. SDL_Error: " << SDL_GetError() << endl;
				
				mainMenu.renderMainMenu(gRenderer);
			}

			if (creditsScreen.getAlive() == true)
			{
				if ( SDL_RenderClear(gRenderer) < 0 )
        			cout << "SDL_RenderClear failed. SDL_Error: " << SDL_GetError() << endl;

				creditsScreen.renderCredits(gRenderer);
			}

			if (gameScreen.getAlive() == true)
			{
				if ( SDL_RenderClear(gRenderer) < 0 )
        			cout << "SDL_RenderClear failed. SDL_Error: " << SDL_GetError() << endl;

				if ( gameScreen.time.getTicks() / 1000.f >= 60.f)
				{
					tempScoreString = to_string(gameScreen.score);
					scoreScreen.scoreWord.changeWord(tempScoreString);

					gameScreen.setAlive(false);
					// mainMenu.setAlive(true);
					scoreScreen.setAlive(true);

					gameScreen.endGame();		// now the gameScreen attributes will be reset

				}

				tempTime = 60 - ( (int) gameScreen.time.getTicks() / 1000.f);
				tempTimeString = to_string(tempTime);
				gameScreen.timeWord.changeWord(tempTimeString);

				// cout << tempTimeString << endl;

				// tempNoOfMasks = gameScreen.noOfMasks;
				tempNoOfMasksString = to_string(gameScreen.noOfMasks);
				gameScreen.noOfMasksWord.changeWord(tempNoOfMasksString);

				// tempNoOfSanitizer = gameScreen.noOfSanitizer;
				tempNoOfSanitizerString = to_string(gameScreen.noOfSanitizer);
				gameScreen.noOfSanitizerWord.changeWord(tempNoOfSanitizerString);


				if ( (gameScreen.maskUpTime.getTicks() / 1000.f) >= 10 )
				{
					gameScreen.player.isWearingMask = false;
					gameScreen.maskUpTime.stop();
				}

				if ( (gameScreen.sanitizerUpTime.getTicks() / 1000.f) >= 25 )
				{
					gameScreen.player.isSanitized = false;
					gameScreen.sanitizerUpTime.stop();
				}

				if (gameScreen.player.getDstRect().x >= 150 && gameScreen.player.getDstRect().x <= 150+60)
				{
					gameScreen.player.isStandingOnMark = true;
				}
				else if (gameScreen.player.getDstRect().x >= 150+312 && gameScreen.player.getDstRect().x <= 150+312+60)
				{
					gameScreen.player.isStandingOnMark = true;
				}
				else if (gameScreen.player.getDstRect().x >= 150+312+312 && gameScreen.player.getDstRect().x <= 150+312+312+60)
				{
					gameScreen.player.isStandingOnMark = true;
				}
				else if (gameScreen.player.getDstRect().x >= 150+312+312+312 && gameScreen.player.getDstRect().x <= 150+312+312+312+60)
				{
					gameScreen.player.isStandingOnMark = true;
				}
				else
				{
					gameScreen.player.isStandingOnMark = false;
				}

				gameScreen.renderGameScreen(gRenderer);

				chaiWala.renderPerson(gRenderer);
				walkingGirl.renderPerson(gRenderer);
				walkingBoy.renderPerson(gRenderer);
				
			}

			if (shopScreen.getAlive() == true)
			{
				if ( SDL_RenderClear(gRenderer) < 0 )
        			cout << "SDL_RenderClear failed. SDL_Error: " << SDL_GetError() << endl;

				// tempNoOfMasks = gameScreen.noOfMasks;
				tempNoOfMasksString = to_string(gameScreen.noOfMasks);
				shopScreen.noOfMasksWord.changeWord(tempNoOfMasksString);

				// tempNoOfSanitizer = gameScreen.noOfSanitizer;
				tempNoOfSanitizerString = to_string(gameScreen.noOfSanitizer);
				shopScreen.noOfSanitizerWord.changeWord(tempNoOfSanitizerString);
				
				shopScreen.renderShop(gRenderer, &gameScreen);
			}

			if (scoreScreen.getAlive() == true)
			{
				scoreScreen.renderScoreScreen(gRenderer);

			}

			SDL_RenderPresent(gRenderer);
		}
	}

    close();
}