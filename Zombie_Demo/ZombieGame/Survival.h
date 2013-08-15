#ifndef SURVIVAL_H_INCLUDED
#define SURVIVAL_H_INCLUDED

#include "GameState.h"
#include <SDL.h>
#include "ZombieKiller.h"
#include "Interface.h"

class Survival : public GameState
{
public:
	ZombieKiller zombieKiller;//the charecter you are controling
	SDL_Surface *Level;//the huge level surface
	Interface face;

	//constructors
	Survival();
	~Survival();

	//Main loop functions
    void handle_events();
    void logic();
    void render();
};

#endif//SURVIVAL_H_INCLUDED