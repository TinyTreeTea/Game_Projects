#include "ghost.h"
#include "SDL.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "SDL_ttf.h"
#define PIE 3.14159265
Ghost::~Ghost()
{
	for(int i = 0;i < 4;++i)
		SDL_FreeSurface(color[i]);
}
void Ghost::ghostReset(int xMiddle,int yMiddle,int speed,int state,int counter)
{
	w = h = 24;
	this->xMiddle = xMiddle;
	this->yMiddle = yMiddle;
	x = xMiddle - 12;
	y = yMiddle - 12;
	if(state == 2)
	{
		if(std::rand() % 2 == 0)
		{
			xvel = speed;
			yvel = 0;
		}
		else
		{
			xvel = -speed;
			yvel = 0;
		}
	}
	else
	{
		xvel = 0;
		yvel = -speed;
	}
	this->speed = speed;
	this->state = state;
	this->counter = counter;
}
Ghost::Ghost(int xMiddle,int yMiddle,SDL_Surface *color,int speed,int state,int counter)
{
	w = h = 24;
	this->xMiddle = xMiddle;
	this->yMiddle = yMiddle;
	x = xMiddle - 12;
	y = yMiddle - 12;
	if(state == 2)
	{
		if(std::rand() % 2 == 0)
		{
			xvel = speed;
			yvel = 0;
		}
		else
		{
			xvel = -speed;
			yvel = 0;
		}
	}
	else
	{
		xvel = 0;
		yvel = -speed;
	}
	extern SDL_Surface *load_image( std::string filename );
	this->color[0] = color;
	this->color[1] = load_image("images/darkBlueGhost.png");
	this->color[2] = load_image("images/whiteGhost.png");
	this->color[3] = load_image("images/ghostEyes.png");
	this->speed = speed;
	this->state = state;
	this->counter = counter;
}
void Ghost::show()
{
	extern SDL_Surface *screen;
	extern void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
	if(state < 3)
		apply_surface(x,y,color[0],screen);
	else if(state == 3)
	{
		if(timer.get_ticks() > 4500 && timer.get_ticks() % 2 == 0)
			apply_surface(x,y,color[2],screen);
		else 
			apply_surface(x,y,color[1],screen);
	}
	else
	{
		apply_surface(x,y,color[3],screen);
	}
}
extern Uint32* get_pixel32( SDL_Surface *surface, int x, int y );
bool Ghost::checkCollisionWithUpWall()
{
	extern SDL_Surface *background;
	if(SDL_MUSTLOCK(background))
		SDL_LockSurface(background);
	Uint8 *checkCollision = (Uint8 *)get_pixel32(background, xMiddle, yMiddle - 1);
	if(checkCollision[0] != 2 || checkCollision[1] != 1 || checkCollision[2] != 1)
		return true;
	if(SDL_MUSTLOCK(background))
		SDL_UnlockSurface(background);
	return false;
}
bool Ghost::checkCollisionWithRightWall()
{
	extern SDL_Surface *background;
	if(SDL_MUSTLOCK(background))
		SDL_LockSurface(background);
	Uint8 *checkCollision = (Uint8 *)get_pixel32(background, xMiddle + 1, yMiddle);
	if(checkCollision[0] != 2 || checkCollision[1] != 1 || checkCollision[2] != 1)
		return true;
	if(SDL_MUSTLOCK(background))
		SDL_UnlockSurface(background);
	return false;
}
bool Ghost::checkCollisionWithDownWall()
{
	extern SDL_Surface *background;
	if(SDL_MUSTLOCK(background))
		SDL_LockSurface(background);
	Uint8 *checkCollision = (Uint8 *)get_pixel32(background, xMiddle , yMiddle + 1);
	if(checkCollision[0] != 2 || checkCollision[1] != 1 || checkCollision[2] != 1)
		return true;
	if(SDL_MUSTLOCK(background))
		SDL_UnlockSurface(background);
	return false;
}
bool Ghost::checkCollisionWithLeftWall()
{
	extern SDL_Surface *background;
	if(SDL_MUSTLOCK(background))
		SDL_LockSurface(background);
	Uint8 *checkCollision = (Uint8 *)get_pixel32(background, xMiddle -1, yMiddle);
	if(checkCollision[0] != 2 || checkCollision[1] != 1 || checkCollision[2] != 1)
		return true;
	if(SDL_MUSTLOCK(background))
		SDL_UnlockSurface(background);
	return false;
}
bool Ghost::checkCollisionWithPacman(Pacman &pacman)
{
	if(pacman.x + w - 4 > x + 3 && pacman.x + 4 < x + w - 3 && pacman.y + w - 4 > y + 3  && pacman.y + 4 < y + w - 3)
		return true;
	return false;
}
void Ghost::move(Uint32 deltaTicks,Pacman &pacman,Ghost *ghost)
{
	if(state == 2)
	{
		if(xMiddle == 93 && yMiddle == 198)
		{
			xMiddle = 504;
			x += 409;
			return;
		}
		else if(xMiddle == 505 && yMiddle == 198)
		{
			xMiddle = 94;
			x -= 409;
			return;
		}
		int randomNumber = std::rand();
		if(xvel < 0)
		{
			bool left = checkCollisionWithLeftWall();
			bool up = checkCollisionWithUpWall();
			bool down = checkCollisionWithDownWall();
			if(!up && !left && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,left,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else if(deltaY < 0)
				{
					up = deltaY * -1;
					down = 1;
				}
				else
				{
					up = 1;
					down = 1;
				}
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (up + down + left);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else if(newPath < up + down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!up && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle;
				int up,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else
				{
					up = deltaY;
					down = 1;
				}
				int newPath = std::rand() % (up + down);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else 
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
			}
			else if(!up && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,left;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (up + left);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!down && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,left;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (down + left);
				if(newPath < down)
				{
					xvel = 0;
					yvel = +speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -speed;
				--y;
				--yMiddle;
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed;
				++y;
				++yMiddle;
			}
			else
			{
				xvel = -speed;
				yvel = 0;
				int checkToIncrease3 = (int)x;
				x += xvel *(deltaTicks / 1000.f);
				if((int)x < checkToIncrease3)
					--xMiddle;
			}
		}
		else if(xvel > 0)
		{
			bool right = checkCollisionWithRightWall();
			bool up = checkCollisionWithUpWall();
			bool down = checkCollisionWithDownWall();
			if(!up && !right && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else if(deltaY < 0)
				{
					up = deltaY * -1;
					down = 1;
				}
				else
				{
					up = 1;
					down = 1;
				}
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (up + down + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else if(newPath < up + down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle;
				int up,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else
				{
					up = deltaY;
					down = 1;
				}
				int newPath = std::rand() % (up + down);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else 
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
			}
			else if(!up && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,right;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = +speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -speed;
				--y;
				--yMiddle;
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed;
				++y;
				++yMiddle;
			}
			else
			{
				xvel = speed;
				yvel = 0;
				int checkToIncrease2 = (int)x;
				x += xvel * (deltaTicks / 1000.f);
				if((int)x > checkToIncrease2)
					++xMiddle;
			}
		}
		else if(yvel < 0)
		{
			bool left = checkCollisionWithLeftWall();
			bool up = checkCollisionWithUpWall();
			bool right = checkCollisionWithRightWall();
			if(!up && !left && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right,left;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (up + left + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else if(newPath < up + left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,left;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!right && !left)
			{
				int deltaX = pacman.xMiddle - xMiddle;
				int right,left;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (left + right);
				if(newPath < left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -speed;
				int checkToIncrease1 = (int)y;
				y += yvel * (deltaTicks / 1000.f);
				if((int)y < checkToIncrease1)
					--yMiddle;
			}
			else if(!right)
			{
				xvel = speed;
				yvel = 0;
				++x;
				++xMiddle;
			}
			else
			{
				xvel = -speed;
				yvel = 0;
				--x;
				--xMiddle;
			}
		}
		else
		{
			bool left = checkCollisionWithLeftWall();
			bool down = checkCollisionWithDownWall();
			bool right = checkCollisionWithRightWall();
			if(!down && !left && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,right,left;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (down + left + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else if(newPath < down + left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,right;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,left;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!right && !left)
			{
				int deltaX = pacman.xMiddle - xMiddle;
				int right,left;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (left + right);
				if(newPath < left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed;
				int checkToIncrease3 = (int)y;
				y += yvel *(deltaTicks / 1000.f);
				if((int)y > checkToIncrease3)
					++yMiddle;
			}
			else if(!right)
			{
				xvel = speed;
				yvel = 0;
				++x;
				++xMiddle;
			}
			else
			{
				xvel = -speed;
				yvel = 0;
				--x;
				--xMiddle;
			}
		}
		if(checkCollisionWithPacman(pacman))
		{
			extern bool breakLoop;
			SDL_Delay(3000);
			--pacman.lives;
			breakLoop = true;
		}
	}
	else if(state == 3)
	{
		if(timer.get_ticks() > 7000)
		{
			state = 2;
			return;
		}
		if(xMiddle == 93 && yMiddle == 198)
		{
			xMiddle = 504;
			x += 409;
			return;
		}
		else if(xMiddle == 505 && yMiddle == 198)
		{
			xMiddle = 94;
			x -= 409;
			return;
		}
		if(xvel < 0)
		{
			bool left = checkCollisionWithLeftWall();
			bool up = checkCollisionWithUpWall();
			bool down = checkCollisionWithDownWall();
			if(!up && !left && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,left,down;
				if(deltaY > 0)
				{
					up = deltaY;
					down = 1;
				}
				else if(deltaY < 0)
				{
					down = deltaY * -1;
					up = 1;
				}
				else
				{
					down = 1;
					up = 1;
				}
				if(deltaX < 0)
					left = 1;
				else
					left = deltaX * -1;
				int newPath = std::rand() % (up + down + left);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed / 2);
					--y;
					--yMiddle;
				}
				else if(newPath < up + down)
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!up && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle;
				int up,down;
				if(deltaY > 0)
				{
					up = deltaY;
					down = 1;
				}
				else
				{
					down = deltaY;
					up = 1;
				}
				int newPath = std::rand() % (up + down);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else 
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
			}
			else if(!up && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,left;
				if(deltaY < 0)
					up = 1;
				else
					up = deltaY;
				if(deltaX < 0)
					left = 1;
				else
					left = deltaX;
				int newPath = std::rand() % (up + left);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!down && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,left;
				if(deltaY > 0)
					down = 1;
				else
					down = deltaY;
				if(deltaX < 0)
					left = 1;
				else
					left = deltaX;
				int newPath = std::rand() % (down + left);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -(speed/2);
				--y;
				--yMiddle;
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed/2;
				++y;
				++yMiddle;
			}
			else
			{
				xvel = -(speed/2);
				yvel = 0;
				int checkToIncrease3 = (int)x;
				x += xvel *(deltaTicks / 1000.f);
				if((int)x < checkToIncrease3)
					--xMiddle;
			}
		}
		else if(xvel > 0)
		{
			bool right = checkCollisionWithRightWall();
			bool up = checkCollisionWithUpWall();
			bool down = checkCollisionWithDownWall();
			if(!up && !right && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right,down;
				if(deltaY > 0)
				{
					up = deltaY;
					down = 1;
				}
				else if(deltaY < 0)
				{
					down = deltaY * -1;
					up = 1;
				}
				else
				{
					up = 1;
					down = 1;
				}
				if(deltaX > 0)
					right = 1;
				else
					right = deltaX;
				int newPath = std::rand() % (up + down + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else if(newPath < up + down)
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !down)
			{
				int deltaY = pacman.yMiddle - yMiddle;
				int up,down;
				if(deltaY > 0)
				{
					up = deltaY;
					down = 1;
				}
				else
				{
					down = deltaY;
					up = 1;
				}
				int newPath = std::rand() % (up + down);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else 
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
			}
			else if(!up && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right;
				if(deltaY < 0)
					up = 1;
				else
					up = deltaY * -1;
				if(deltaX > 0)
					right = 1;
				else
					right = deltaX;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,right;
				if(deltaY > 0)
					down = 1;
				else
					down = deltaY * -1;
				if(deltaX > 0)
					right = 1;
				else
					right = deltaX * -1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -(speed/2);
				--y;
				--yMiddle;
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed/2;
				++y;
				++yMiddle;
			}
			else
			{
				xvel = speed/2;
				yvel = 0;
				int checkToIncrease2 = (int)x;
				x += xvel * (deltaTicks / 1000.f);
				if((int)x > checkToIncrease2)
					++xMiddle;
			}
		}
		else if(yvel < 0)
		{
			bool left = checkCollisionWithLeftWall();
			bool up = checkCollisionWithUpWall();
			bool right = checkCollisionWithRightWall();
			if(!up && !left && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right,left;
				if(deltaY < 0)
					up = 1;
				else
					up = deltaY;
				if(deltaX > 0)
				{
					left = deltaX;
					right = 1;
				}
				else if(deltaX < 0)
				{
					left = 1;
					right = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (up + left + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else if(newPath < up + left)
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,right;
				if(deltaY < 0)
					up = 1;
				else
					up = deltaY * -1;
				if(deltaX > 0)
					right = 1;
				else
					right = deltaX;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int up,left;
				if(deltaY < 0)
					up = 1;
				else
					up = deltaY;
				if(deltaX < 0)
					left = 1;
				else
					left = deltaX * -1;
				int newPath = std::rand() % (up + left);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -(speed/2);
					--y;
					--yMiddle;
				}
				else
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!right && !left)
			{
				int deltaX = pacman.xMiddle - xMiddle;
				int right,left;
				if(deltaX > 0)
				{
					left = deltaX;
					right = 1;
				}
				else if(deltaX < 0)
				{
					left = 1;
					right = deltaX * -1;
				}
				else
				{
					left = 1;
					right = 1;
				}
				int newPath = std::rand() % (left + right);
				if(newPath < left)
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -(speed/2);
				int checkToIncrease1 = (int)y;
				y += yvel * (deltaTicks / 1000.f);
				if((int)y < checkToIncrease1)
					--yMiddle;
			}
			else if(!right)
			{
				xvel = speed/2;
				yvel = 0;
				++x;
				++xMiddle;
			}
			else
			{
				xvel = -(speed/2);
				yvel = 0;
				--x;
				--xMiddle;
			}
		}
		else
		{
			bool left = checkCollisionWithLeftWall();
			bool down = checkCollisionWithDownWall();
			bool right = checkCollisionWithRightWall();
			if(!down && !left && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,right,left;
				if(deltaY > 0)
					down = 1;
				else
					down = deltaY;
				if(deltaX > 0)
				{
					left = deltaX;
					right = 1;
				}
				else if(deltaX < 0)
				{
					left = 1;
					right = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (down + left + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
				else if(newPath < down + left)
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !right)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,right;
				if(deltaY > 0)
					down = 1;
				else
					down = deltaY;
				if(deltaX > 0)
					right = 1;
				else
					right = deltaX;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !left)
			{
				int deltaY = pacman.yMiddle - yMiddle,deltaX = pacman.xMiddle - xMiddle;
				int down,left;
				if(deltaY > 0)
					down = 1;
				else
					down = deltaY;
				if(deltaX < 0)
					left = 1;
				else
					left = deltaX * -1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed/2;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!right && !left)
			{
				int deltaX = pacman.xMiddle - xMiddle;
				int right,left;
				if(deltaX > 0)
				{
					left = deltaX;
					right = 1;
				}
				else if(deltaX < 0)
				{
					left = 1;
					right = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (left + right);
				if(newPath < left)
				{
					xvel = -(speed/2);
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed/2;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed/2;
				int checkToIncrease3 = (int)y;
				y += yvel *(deltaTicks / 1000.f);
				if((int)y > checkToIncrease3)
					++yMiddle;
			}
			else if(!right)
			{
				xvel = speed/2;
				yvel = 0;
				++x;
				++xMiddle;
			}
			else
			{
				xvel = -(speed/2);
				yvel = 0;
				--x;
				--xMiddle;
			}
		}
		if(checkCollisionWithPacman(pacman))
		{
			extern SDL_Surface *screen;
			extern void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
			extern TTF_Font *score;
			extern SDL_Color textColor;
			char buffer[5];
			if(pacman.bonusEatingScore == 0)
			{
				pacman.bonusEatingScore = 200;
				pacman.score += pacman.bonusEatingScore;
				state = 4;
			}
			else
			{
				pacman.bonusEatingScore += pacman.bonusEatingScore;
				pacman.score += pacman.bonusEatingScore;
				state = 4;
			}
		}
	}
	else if(state == 1)
	{
		if(xMiddle == 299)
		{
			xvel = 0;
			yvel = -speed;
			int checkToIncrease1 = (int)y;
			y += yvel * (deltaTicks / 1000.f);
			if((int)y < checkToIncrease1)
				--yMiddle;
			if(yMiddle == 161)
			{
				state = 2;
				if(std::rand() % 2 == 0)
				{
					xvel = speed;
					yvel = 0;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
				}
			}
		}
		else if(xMiddle < 299)
		{
			int checkToIncrease2 = (int)x;
			x += xvel * (deltaTicks / 1000.f);
			if((int)x > checkToIncrease2)
				++xMiddle;
		}
		else
		{
			xvel = -speed;
			yvel = 0;
			int checkToIncrease3 = (int)x;
			x += xvel *(deltaTicks / 1000.f);
			if((int)x < checkToIncrease3)
				--xMiddle;
		}
	}
	else if(state == 0)
	{
		if(yMiddle == 208)
		{
			--counter;
			--yMiddle;
			--y;
			yvel = -speed;
		}
		else if(yMiddle == 188)
		{
			if(counter < 0)
			{
				state = 1;
				if(xMiddle == 268)
				{
					xvel = speed;
					yvel = 0;
				}
				else if(xMiddle == 328)
				{
					xvel = -speed;
					yvel = 0;
				}
			}
			--counter;
			++yMiddle;
			++y;
			yvel = speed;
		}
		else if(yvel < 0)
		{
			int checkToIncrease1 = (int)y;
			y += yvel * (deltaTicks / 1000.f);
			if((int)y < checkToIncrease1)
				--yMiddle;
		}
		else
		{
			int checkToIncrease1 = (int)y;
			y += yvel * (deltaTicks / 1000.f);
			if((int)y > checkToIncrease1)
				++yMiddle;
		}
	}
	else if(state == 4)
	{
		speed *= 2;
		if(xMiddle == 299 && yMiddle > 160 && yMiddle < 188)
		{
			xvel = 0;
			yvel = speed;
			int checkToIncrease1 = (int)y;
			y += yvel * (deltaTicks / 1000.f);
			if((int)y > checkToIncrease1)
				++yMiddle;
			if(yMiddle == 188)
				state = 1;
			speed /= 2;
			return;
		}
		if(xMiddle == 93 && yMiddle == 198)
		{
			xMiddle = 504;
			x += 409;
			speed /= 2;
			return;
		}
		else if(xMiddle == 505 && yMiddle == 198)
		{
			xMiddle = 94;
			x -= 409;
			speed /= 2;
			return;
		}
		int randomNumber = std::rand();
		if(xvel < 0)
		{
			bool left = checkCollisionWithLeftWall();
			bool up = checkCollisionWithUpWall();
			bool down = checkCollisionWithDownWall();
			if(!up && !left && !down)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int up,left,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else if(deltaY < 0)
				{
					up = deltaY * -1;
					down = 1;
				}
				else
				{
					up = 1;
					down = 1;
				}
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (up + down + left);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else if(newPath < up + down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!up && !down)
			{
				int deltaY = 161 - yMiddle;
				int up,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else
				{
					up = deltaY;
					down = 1;
				}
				int newPath = std::rand() % (up + down);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else 
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
			}
			else if(!up && !left)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int up,left;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (up + left);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!down && !left)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int down,left;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (down + left);
				if(newPath < down)
				{
					xvel = 0;
					yvel = +speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -speed;
				--y;
				--yMiddle;
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed;
				++y;
				++yMiddle;
			}
			else
			{
				xvel = -speed;
				yvel = 0;
				int checkToIncrease3 = (int)x;
				x += xvel *(deltaTicks / 1000.f);
				if((int)x < checkToIncrease3)
					--xMiddle;
			}
		}
		else if(xvel > 0)
		{
			bool right = checkCollisionWithRightWall();
			bool up = checkCollisionWithUpWall();
			bool down = checkCollisionWithDownWall();
			if(!up && !right && !down)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int up,right,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else if(deltaY < 0)
				{
					up = deltaY * -1;
					down = 1;
				}
				else
				{
					up = 1;
					down = 1;
				}
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (up + down + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else if(newPath < up + down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !down)
			{
				int deltaY = 161 - yMiddle;
				int up,down;
				if(deltaY > 0)
				{
					down = deltaY;
					up = 1;
				}
				else
				{
					up = deltaY;
					down = 1;
				}
				int newPath = std::rand() % (up + down);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else 
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
			}
			else if(!up && !right)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int up,right;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !right)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int down,right;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = +speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -speed;
				--y;
				--yMiddle;
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed;
				++y;
				++yMiddle;
			}
			else
			{
				xvel = speed;
				yvel = 0;
				int checkToIncrease2 = (int)x;
				x += xvel * (deltaTicks / 1000.f);
				if((int)x > checkToIncrease2)
					++xMiddle;
			}
		}
		else if(yvel < 0)
		{
			bool left = checkCollisionWithLeftWall();
			bool up = checkCollisionWithUpWall();
			bool right = checkCollisionWithRightWall();
			if(!up && !left && !right)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int up,right,left;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (up + left + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else if(newPath < up + left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !right)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int up,right;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up && !left)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int up,left;
				if(deltaY < 0)
					up = deltaY * -1;
				else
					up = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (up + right);
				if(newPath < up)
				{
					xvel = 0;
					yvel = -speed;
					--y;
					--yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!right && !left)
			{
				int deltaX = 299 - xMiddle;
				int right,left;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (left + right);
				if(newPath < left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!up)
			{
				xvel = 0;
				yvel = -speed;
				int checkToIncrease1 = (int)y;
				y += yvel * (deltaTicks / 1000.f);
				if((int)y < checkToIncrease1)
					--yMiddle;
			}
			else if(!right)
			{
				xvel = speed;
				yvel = 0;
				++x;
				++xMiddle;
			}
			else
			{
				xvel = -speed;
				yvel = 0;
				--x;
				--xMiddle;
			}
		}
		else
		{
			bool left = checkCollisionWithLeftWall();
			bool down = checkCollisionWithDownWall();
			bool right = checkCollisionWithRightWall();
			if(!down && !left && !right)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int down,right,left;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (down + left + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else if(newPath < down + left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !right)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int down,right;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX > 0)
					right = deltaX;
				else
					right = 1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down && !left)
			{
				int deltaY = 161 - yMiddle,deltaX = 299 - xMiddle;
				int down,left;
				if(deltaY > 0)
					down = deltaY;
				else
					down = 1;
				if(deltaX < 0)
					left = deltaX * -1;
				else
					left = 1;
				int newPath = std::rand() % (down + right);
				if(newPath < down)
				{
					xvel = 0;
					yvel = speed;
					++y;
					++yMiddle;
				}
				else
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
			}
			else if(!right && !left)
			{
				int deltaX = 299 - xMiddle;
				int right,left;
				if(deltaX > 0)
				{
					right = deltaX;
					left = 1;
				}
				else if(deltaX < 0)
				{
					right = 1;
					left = deltaX * -1;
				}
				else
				{
					right = 1;
					left = 1;
				}
				int newPath = std::rand() % (left + right);
				if(newPath < left)
				{
					xvel = -speed;
					yvel = 0;
					--x;
					--xMiddle;
				}
				else
				{
					xvel = speed;
					yvel = 0;
					++x;
					++xMiddle;
				}
			}
			else if(!down)
			{
				xvel = 0;
				yvel = speed;
				int checkToIncrease3 = (int)y;
				y += yvel *(deltaTicks / 1000.f);
				if((int)y > checkToIncrease3)
					++yMiddle;
			}
			else if(!right)
			{
				xvel = speed;
				yvel = 0;
				++x;
				++xMiddle;
			}
			else
			{
				xvel = -speed;
				yvel = 0;
				--x;
				--xMiddle;
			}
		}
		speed /= 2;
	}
}