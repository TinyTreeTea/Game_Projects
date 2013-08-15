#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include "SDL/SDL.h"
#include <time.h>

extern SDL_Event event;
class Slot
{
public:
	bool isOccupied;
	int color;
	Slot()
	{
		isOccupied = false;
	}
	operator bool()
	{
		return isOccupied;
	}
};
class Board
{
public:
    int score;
    int shape;//the current shape of our shape
    int state;//the state of our shape

    int latitude[10];//the collision levels of the current shape
    int x, y;//where we blitted the image
    Slot slots[18][10];//true if the place is occupied and false if not
    Board();
    void eraseLine(int erasingPoint);
    void checkLine();
    bool checkCollision1();
    bool checkCollision2();
    bool checkCollisionWithLeftWall();
    bool checkCollisionWithRightWall();
    bool goDown();
    bool rotate();
    bool moveRight();
    bool moveLeft();
    bool handleInput();
};
#endif // BOARD_H_INCLUDED
