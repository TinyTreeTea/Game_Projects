#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "GameState.h"
#include "LazyFooFunctionsAndConstants.h"
#include "ZombieKiller.h"

/*Globals*/
//The surfaces
extern SDL_Surface *screen;
extern SDL_Surface *background;

//The event structure
extern SDL_Event event;

//The font that's going to be used
extern TTF_Font *font;

//The color of the font
extern SDL_Color textColor;

//State variables
extern int stateID;
extern int nextState;

//Game state object
extern GameState *currentState;

//the clip of the sprite sheet
extern SDL_Rect clip[MODERATION];

//zombieKiller's sprite sheet.for rotation.and the versions in the animation
extern SDL_Surface *zombieKillerSurfaceSpriteSheet;
extern SDL_Surface *zombieKillerSurfaceSpriteSheet1;
extern SDL_Surface *zombieKillerSurfaceSpriteSheet2;
extern SDL_Surface *zombieKillerSurfaceSpriteSheet3;
extern SDL_Surface *zombieKillerSurfaceSpriteSheet4;
extern SDL_Surface *zombieKillerSurfaceSpriteSheet5;
extern SDL_Surface *zombieKillerSurfaceSpriteSheetMinus1;
extern SDL_Surface *zombieKillerSurfaceSpriteSheetMinus2;
extern SDL_Surface *zombieKillerSurfaceSpriteSheetMinus3;
extern SDL_Surface *zombieKillerSurfaceSpriteSheetMinus4;
extern SDL_Surface *zombieKillerSurfaceSpriteSheetMinus5;

//the gun explosion
extern SDL_Surface * sparksSpriteSheet;

//the bullet in all directions
extern SDL_Surface * bulletSpriteSheet;

//the only zombie for now and its spritesheet
extern SDL_Surface * zombieSpriteSheet;

//zombieKiller's clip to choose the picture inside the zombieKiller's sprite sheet
extern SDL_Rect *zombieKillerClip;

//zombieKillerClip length and also the amout of different rotations the zombieKiller can have
extern int zombieKillerClipLength;

//each angle has a different tip of gun and stuff like that.
extern Information * zombieInformation;

//the list of spawning monsters
extern SpawnData * spawndata;


extern SDL_Surface * bloodSpriteSheet;

extern SDL_Surface * deadSpriteSheet;

//the amount of frames passed
extern long framesPassed;

extern int zombieKilled;

#endif // GLOBALS_H_INCLUDED