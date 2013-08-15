#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "LazyFooFunctionsAndConstants.h"
#include "ZombieKiller.h"

class Interface
{
public:
	int life;
	int maxLife;
	int gun;
	int zombies;
	int deadZombies;
	int seconds;
	int xZombieKiller, yZombieKiller;
	SDL_Surface *topLeftBox;
	SDL_Surface *lifeBar;
	SDL_Surface *gunPicture;
	SDL_Surface *amountOfLiveZombies;
	SDL_Surface *amountOfDeadZombies;
	ZombieKiller *character;
	Interface(ZombieKiller *zombieKiller);
	~Interface();
	void update();
	void show();
};

#endif//INTERFACE_H_INCLUDED