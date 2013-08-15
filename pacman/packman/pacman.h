#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED
#include "SDL.h"
#include <string>

class Pacman
{
public:
	int lives;
	int bonusEatingScore;
	int w, h;
	float x, y;//the x and y properties of the pacman surface
	float xvel, yvel;//pacmans x velocity, pacmans y velocity
	int xMiddle, yMiddle;//pacmans x and y middle properties, ment for moving
	int	xMoveToo, yMoveToo;//where pacman is actually suposed to be heading too
	int direction;//pacman can have 4 directions, 0 = up, 1 = right, 2 = down, 3 = left
	/*static*/ SDL_Surface *pacmanSurfaces[5];//remember to delete

	int score;//pacmans score so far
	Pacman();//pacmans constructor initializes him to default place
	~Pacman();
	void pacmanReset(int score,int lives);
	void handle_input();//will handle pacmans events
	bool checkCollisionWithUpWall();//returns true if pacman collided with the wall and false if he did not
	bool checkCollisionWithRightWall();//returns true if pacman collided with the wall and false if he did not
	bool checkCollisionWithDownWall();//returns true if pacman collided with the wall and false if he did not
	bool checkCollisionWithLeftWall();//returns true if pacman collided with the wall and false if he did not

	void move(Uint32 deltaTicks);/*moves pacman accordinglly to xvel and yvel
	note that this function will check pacmans members(xMoveToo, yMoveToo) and if needed it will also change
	the members (xvel, yvel)*/
	void show(bool mouthOpen);//apply pacman on the screen
};
/*extern SDL_Surface *load_image( std::string filename );
SDL_Surface *Pacman::pacmanSurfaces[5] = {load_image("images/pacmanUp.png"),load_image("images/pacmanRight.png"),
	load_image("images/pacmanDown.png"),load_image("images/pacmanLeft.png"),load_image("images/pacmanLeft.png")};*/
#endif //PACMAN_H_INCLUDED