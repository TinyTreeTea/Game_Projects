#include "Interface.h"
#include "ZombieKiller.h"
#include "Globals.h"

Interface::Interface(ZombieKiller *zombieKiller)
{
	character = zombieKiller;
	amountOfDeadZombies = NULL;
	amountOfLiveZombies = NULL;
	update();
	topLeftBox = load_image("Images/TopLeftBox.bmp",true);
	SDL_SetAlpha(topLeftBox,SDL_SRCALPHA,128);
	gunPicture = load_image("Images/Gun.bmp",true);
	lifeBar = SDL_CreateRGBSurface(SDL_SWSURFACE,50,7,24,0xff0000,0xff00,0xff,0);
}

void Interface::update()
{
	if(amountOfDeadZombies != NULL)
	{
		SDL_FreeSurface(amountOfDeadZombies);
		SDL_FreeSurface(amountOfLiveZombies);
	}
	life = character->life;
	maxLife = 100;
	gun = 0;
	zombies = character->zombieCount;
	deadZombies = character->deadZombieCount;
	seconds = framesPassed / FRAMES_PER_SECOND;
	xZombieKiller = character->collisionBox.x + character->collisionBox.w / 2;
	yZombieKiller = character->collisionBox.y + character->collisionBox.h / 2;
	amountOfDeadZombies = TTF_RenderText_Solid(font, intToString(character->deadZombieCount).c_str(), textColor);
	amountOfLiveZombies = TTF_RenderText_Solid(font, intToString(character->zombieCount).c_str(), textColor);
}

void Interface::show()
{
	apply_surface(0,0,topLeftBox,screen);
	apply_surface(150,0,gunPicture,screen);
	SDL_FillRect(lifeBar,NULL,SDL_MapRGB(lifeBar->format,0,0,0));
	int part = lifeBar->w * (life+0.0)/maxLife;
	SDL_Rect black;
	black.x = black.y = 0;
	black.w = part;
	black.h = lifeBar->h;
	SDL_FillRect(lifeBar,&black,SDL_MapRGB(lifeBar->format,255,0,0));
	apply_surface(44,39,lifeBar,screen);
	apply_surface(10, 10, amountOfDeadZombies, screen);
	apply_surface(10, 50, amountOfLiveZombies, screen);
}

Interface::~Interface()
{
	SDL_FreeSurface(topLeftBox);
	SDL_FreeSurface(gunPicture);
	SDL_FreeSurface(lifeBar);
}