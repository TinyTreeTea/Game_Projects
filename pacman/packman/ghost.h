#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "SDL.h"
#include "pacman.h"
#include "timer.h"

class Ghost
{
public:
	Timer timer;
	int w, h;//the width and height of the ghost picture
	int xvel, yvel;/*the velocity of where the ghost is going
	it can only be changed when the ghost has a turning option*/
	float x, y;//where to apply the ghost
	int xMiddle, yMiddle;//where the ghost is on the invisible line
	SDL_Surface *color[4];//the ghosts surface
	int speed;
	int state;//0 if its bouncing inside wall, 1 if its going threw all and 2 for ghosts chasing,3 for ghosts running
	int counter;//how many times will a ghost have to base in corners until released,only send to constructor if (state == 0)
	Ghost(int xMiddle,int yMiddle,SDL_Surface *color,int speed,int state,int counter = 0);//constructor initializes variables
	~Ghost();
	void ghostReset(int xMiddle,int yMiddle,int speed,int state,int counter = 0);
	bool checkCollisionWithUpWall();//returns true if ghost collided with the wall and false if he did not
	bool checkCollisionWithRightWall();//returns true if ghost collided with the wall and false if he did not
	bool checkCollisionWithDownWall();//returns true if ghost collided with the wall and false if he did not
	bool checkCollisionWithLeftWall();//returns true if ghost collided with the wall and false if he did not
	bool checkCollisionWithPacman(Pacman &pacman);//returns true if ghost collided with pacman,false if not
	void show();//apply ghost on the screen
	void move(Uint32 deltaTicks,Pacman &pacman,Ghost *ghost);//moves ghost according to velocity
};

#endif //GHOST_H_INCLUDED