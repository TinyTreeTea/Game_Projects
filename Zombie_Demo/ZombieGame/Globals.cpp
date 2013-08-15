#include "Globals.h"
#include "LazyFooFunctionsAndConstants.h"
#include "GameState.h"
#include <SDL.h>
#include <fstream>

/*Globals*/
//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;

//The event structure
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = {230, 233, 244};

//State variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

//Game state object
GameState *currentState = NULL;

//the clip of the sprite sheet
SDL_Rect clip[MODERATION];

//zombieKiller's sprite sheet.for rotation.and the version in the animation
SDL_Surface *zombieKillerSurfaceSpriteSheet = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheet1 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheet2 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheet3 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheet4 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheet5 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheetMinus1 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheetMinus2 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheetMinus3 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheetMinus4 = NULL;
SDL_Surface *zombieKillerSurfaceSpriteSheetMinus5 = NULL;

//the gun explosion
SDL_Surface * sparksSpriteSheet = NULL;

//the bullet in all directions
SDL_Surface * bulletSpriteSheet = NULL;

//the only zombie for now and its spritesheet
SDL_Surface * zombieSpriteSheet = NULL;

//zombieKiller's clip to choose the picture inside the zombieKiller's sprite sheet
SDL_Rect *zombieKillerClip = NULL;

//zombieKillerClip length and also the amout of different rotations the zombieKiller can have
int zombieKillerClipLength;

//each angle has different tip of gun and info like that
Information * zombieInformation = NULL;

//the list of spawning monsters
SpawnData * spawndata = NULL;

SDL_Surface * bloodSpriteSheet = NULL;

SDL_Surface * deadSpriteSheet = NULL;

int zombieKilled = 0;
//the amount of frames passed
long framesPassed = 0;
