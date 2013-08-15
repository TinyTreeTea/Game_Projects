#include <SDL.h>
#include "LazyFooFunctionsAndConstants.h"
#include "Globals.h"
#include <iostream>
#include <time.h>
#include "Survival.h"

int main(int argc, char *args[])
{
	//seed random number so you can use the function rand() everywhere
	srand(time(NULL));

    //The frame rate regulator
    Timer fps;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

	/*SDL_Surface *dead = load_image("Images/dead.bmp",true);

	Grid grid(dead);

	SDL_Surface *deadSpriteSheet = NULL;

	grid.saveSpriteSheetAndSaveClip(deadSpriteSheet,32,34,"Images/deadSpriteSheet.bmp","Clips/deadClip");
	/*
	SDL_Surface *zombieKiller1 = load_image("Images/Test1.bmp",true);

	Grid grid1(zombieKiller1);

	SDL_Surface *zombieKillerSpriteSheet1 = NULL;

	grid1.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheet1,47,60,"Images/ZombieKillerSpriteSheet1.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKiller2 = load_image("Images/Test2.bmp",true);

	Grid grid2(zombieKiller2);

	SDL_Surface *zombieKillerSpriteSheet2 = NULL;

	grid2.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheet2,47,60,"Images/ZombieKillerSpriteSheet2.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKiller3 = load_image("Images/Test3.bmp",true);

	Grid grid3(zombieKiller3);

	SDL_Surface *zombieKillerSpriteSheet3 = NULL;

	grid3.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheet3,47,60,"Images/ZombieKillerSpriteSheet3.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKiller4 = load_image("Images/Test4.bmp",true);

	Grid grid4(zombieKiller4);

	SDL_Surface *zombieKillerSpriteSheet4 = NULL;

	grid4.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheet4,47,60,"Images/ZombieKillerSpriteSheet4.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKiller5 = load_image("Images/Test5.bmp",true);

	Grid grid5(zombieKiller5);

	SDL_Surface *zombieKillerSpriteSheet5 = NULL;

	grid5.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheet5,47,60,"Images/ZombieKillerSpriteSheet5.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKillerMinus1 = load_image("Images/TestMinus1.bmp",true);

	Grid gridMinus1(zombieKillerMinus1);

	SDL_Surface *zombieKillerSpriteSheetMinus1 = NULL;

	gridMinus1.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheetMinus1,47,60,"Images/ZombieKillerSpriteSheetMinus1.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKillerMinus2 = load_image("Images/TestMinus2.bmp",true);

	Grid gridMinus2(zombieKillerMinus2);

	SDL_Surface *zombieKillerSpriteSheetMinus2 = NULL;

	gridMinus2.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheetMinus2,47,60,"Images/ZombieKillerSpriteSheetMinus2.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKillerMinus3 = load_image("Images/TestMinus3.bmp",true);

	Grid gridMinus3(zombieKillerMinus3);

	SDL_Surface *zombieKillerSpriteSheetMinus3 = NULL;

	gridMinus3.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheetMinus3,47,60,"Images/ZombieKillerSpriteSheetMinus3.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKillerMinus4 = load_image("Images/TestMinus4.bmp",true);

	Grid gridMinus4(zombieKillerMinus4);

	SDL_Surface *zombieKillerSpriteSheetMinus4 = NULL;

	gridMinus4.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheetMinus4,47,60,"Images/ZombieKillerSpriteSheetMinus4.bmp","Clips/ZombieKillerClip");

	SDL_Surface *zombieKillerMinus5 = load_image("Images/TestMinus5.bmp",true);

	Grid gridMinus5(zombieKillerMinus5);

	SDL_Surface *zombieKillerSpriteSheetMinus5 = NULL;

	gridMinus5.saveSpriteSheetAndSaveClip(zombieKillerSpriteSheetMinus5,47,60,"Images/ZombieKillerSpriteSheetMinus5.bmp","Clips/ZombieKillerClip");*/

    //Set the current state ID
	stateID = STATE_SURVIVAL;

    //Set the current game state object
    currentState = new Survival();

	//checks if your pc can handle the frame rate
	int counter = 0;

	//Timers to keep track of the loop
	Timer eventTimer, logic, renderingTimer, flipTimer;

	eventTimer.start();
	logic.start();
	renderingTimer.start();
	flipTimer.start();
	eventTimer.pause();
	logic.pause();
	renderingTimer.pause();
	flipTimer.pause();

    //While the user hasn't quit
    while( stateID != STATE_EXIT )
    {
        //Start the frame timer
        fps.start();

		eventTimer.unpause();
        //Do state event handling
        currentState->handle_events();
		eventTimer.pause();

		logic.unpause();
        //Do state logic
        currentState->logic();
		logic.pause();

        //Change state if needed
        change_state();

		renderingTimer.unpause();
        //Do state rendering
        currentState->render();
		renderingTimer.pause();

		flipTimer.unpause();
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
		flipTimer.pause();

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
		else
			++counter;

		//increment the amount of frames passed by one
		++framesPassed;
    }

	int eventTime = eventTimer.get_ticks();
	int logicTime = logic.get_ticks();
	int renderingTime = renderingTimer.get_ticks();
	int flipTime = flipTimer.get_ticks();

	//Clean upd
    clean_up();

    return 0;
}
