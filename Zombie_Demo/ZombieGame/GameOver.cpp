#include "GameOver.h"
#include "LazyFooFunctionsAndConstants.h"
#include "Globals.h"
#include <SDL.h>
#include <fstream>

GameOver::GameOver()
{
	std::ifstream highScore("Stuff/ZombiesKilled");
	int oldHighScore;
	highScore >> oldHighScore;
	highScore.close();
	TTF_Font *newFont = TTF_OpenFont("lazy.ttf", 54);
	SDL_Color newTextColor = {0, 0, 0};
	this->highScore = TTF_RenderText_Solid(newFont,intToString(oldHighScore).c_str(),newTextColor);
	this->zombiesKilled = TTF_RenderText_Solid(newFont,intToString(zombieKilled).c_str(),newTextColor);
	gameOverSurface = load_image("Images/GameOver.png");
}

GameOver::~GameOver()
{
	std::ifstream highScore("Stuff/ZombiesKilled");
	int oldHighScore;
	highScore >> oldHighScore;
	highScore.close();
	if(oldHighScore < zombieKilled)
	{
		std::ofstream zombiesKilledFile("Stuff/ZombiesKilled");
		zombiesKilledFile << zombieKilled;
		zombiesKilledFile.close();
	}
	SDL_FreeSurface(gameOverSurface);
	SDL_FreeSurface(zombiesKilled);
}

void GameOver::handle_events()
{
	//While there's events to handle
    while(SDL_PollEvent(&event))
    {
		if(event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
		{
			//If the user has Xed out the window
			if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			{
				//Quit the program
				set_next_state( STATE_EXIT );
			}
		}

		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if(x >= 580 && y >= 347 && x <= 823 && y <= 438)
				{
					//Quit the program
					set_next_state(STATE_SURVIVAL);
				}
				else if(x >= 156 && y >= 351 && x <= 383 && y <= 440)
				{
					//Quit the program
					set_next_state(STATE_EXIT);;
				}
			}
		}
    }
}

void GameOver::logic()
{
}

void GameOver::render()
{
	apply_surface(0, 0, gameOverSurface, screen);
	apply_surface(475, 553, zombiesKilled, screen);
	apply_surface(643, 485, highScore, screen);
}