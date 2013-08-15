#ifndef GAME_OVER_H_INCLUDED
#define GAME_OVER_H_INCLUDED

#include "GameState.h"
#include <SDL.h>
#include <string>

class GameOver : public GameState
{
public:
	SDL_Surface *zombiesKilled;
	SDL_Surface *highScore;
	SDL_Surface *gameOverSurface;

	GameOver();
	~GameOver();

	//Main loop functions
    void handle_events();
    void logic();
    void render();
};

#endif//GAME_OVER_H_INCLUDED