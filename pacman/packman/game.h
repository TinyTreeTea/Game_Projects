#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "pacman.h"
#include "SDL.h"
#include "ghost.h"

class Game
{
private:
	char balls[29][26];// 0 means no ball,1 means normal ball, 2 means special ball
	SDL_Surface *smallBall;
	SDL_Surface *bigBall;
public:
	Game();// nothing special,just a constructor to initialize the members of the class
	~Game();
	void resetBalls();
	bool applyBalls(Pacman &pacman,Ghost ghost[]);// applys the balls on the screen, returns true if pacman is on
	//one of the balls and false if not,the purpose of this is to check if pacman should have 
	//his mouth open or not
};
#endif //GAME_H_INCLUDED