#include "Survival.h"
#include "LazyFooFunctionsAndConstants.h"
#include "Globals.h"

Survival::Survival():face(&zombieKiller)
{
	Level = load_image("Images/BigSpikyGrass.png");
}

Survival::~Survival()
{
	//zombieKiller.~ZombieKiller();
	SDL_FreeSurface(Level);
}

void Survival::handle_events()
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

		//handle's zombieKiller's input
		zombieKiller.handle_input();
    }
}

void Survival::logic()
{
	zombieKiller.move();
	zombieKiller.set_camera();
	zombieKiller.handleMouse();
	zombieKiller.bullet_managment();
	zombieKiller.zombie_managment();
	zombieKiller.changeAnimation();
	zombieKiller.collision_manegment();
	zombieKiller.is_finished();
	face.update();
}

void Survival::render()
{
	apply_surface(0, 0, Level, screen, &zombieKiller.camera);
	zombieKiller.show();
	face.show();
}