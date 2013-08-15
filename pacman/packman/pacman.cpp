#include "pacman.h"

const int pacmansSpeed = 95;
//description of these functions are in the header file
Pacman::~Pacman()
{
	for(int i =0;i < 5;++i)
		SDL_FreeSurface(pacmanSurfaces[i]);
}
void Pacman::pacmanReset(int score,int lives)
{
	x = 289;
	y = 306;
	w = 22;
	h = 22;
	xMiddle = (x + (w / 2));
	yMiddle = (y + (h / 2)) - 1;
	xvel = -pacmansSpeed;
	yvel = 0;
	xMoveToo = -1;
	yMoveToo = 0;
	direction = 3;
	extern SDL_Surface *load_image( std::string filename );
	bonusEatingScore = 0;
	this->score = score;
	this->lives = lives;
}
Pacman::Pacman()
{
	x = 289;
	y = 306;
	w = 22;
	h = 22;
	xMiddle = (x + (w / 2));
	yMiddle = (y + (h / 2)) - 1;
	xvel = -pacmansSpeed;
	yvel = 0;
	xMoveToo = -1;
	yMoveToo = 0;
	score = 0;
	direction = 3;
	extern SDL_Surface *load_image( std::string filename );
	pacmanSurfaces[0] = load_image("images/pacmanUp.png");
	pacmanSurfaces[1] = load_image("images/pacmanRight.png");
	pacmanSurfaces[2] = load_image("images/pacmanDown.png");
	pacmanSurfaces[3] = load_image("images/pacmanLeft.png");
	pacmanSurfaces[4] = load_image("images/pacmanMouthClosed.png");
	bonusEatingScore = 0;
	lives = 3;
}
Uint32* get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Get the requested pixel
    return &(pixels[ ( y * surface->w ) + x ]);
}
bool Pacman::checkCollisionWithUpWall()
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
bool Pacman::checkCollisionWithRightWall()
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
bool Pacman::checkCollisionWithDownWall()
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
bool Pacman::checkCollisionWithLeftWall()
{
	extern SDL_Surface *background;
	if(SDL_MUSTLOCK(background))
		SDL_LockSurface(background);
	Uint8 *checkCollision = (Uint8 *)get_pixel32(background, xMiddle - 1, yMiddle);
	if(checkCollision[0] != 2 || checkCollision[1] != 1 || checkCollision[2] != 1)
		return true;
	if(SDL_MUSTLOCK(background))
		SDL_UnlockSurface(background);
	return false;
}
void Pacman::show(bool mouthOpen)
{
	extern SDL_Surface *screen;
	extern void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
	if(mouthOpen)
		apply_surface(x,y - 2,pacmanSurfaces[direction],screen,&pacmanSurfaces[direction]->clip_rect);
	else
		apply_surface(x,y - 2,pacmanSurfaces[4],screen,&pacmanSurfaces[4]->clip_rect);
	for(int i = 0;i < lives;++i)
		apply_surface(260 + 30 * i,420,pacmanSurfaces[1],screen,&pacmanSurfaces[1]->clip_rect);
}
void Pacman::move(Uint32 deltaTicks)
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
	switch(xMoveToo)
	{
	case -1:
		if(checkCollisionWithLeftWall())
		{
			if(direction != 3)
			{
				switch(direction)
				{
				case 0:
					{
						if(!checkCollisionWithUpWall())
						{
							int checkToIncrease1 = (int)y;
							y += yvel * (deltaTicks / 1000.f);
							if((int)y < checkToIncrease1)
								--yMiddle;
							break;
						}
					}
					break;
				case 1:
					{	if(!checkCollisionWithRightWall())
						{
							int checkToIncrease2 = (int)x;
							x += xvel * (deltaTicks / 1000.f);
							if((int)x > checkToIncrease2)
								++xMiddle;
							break;
						}
					}
					break;
				case 2:
					{	if(!checkCollisionWithDownWall())
						{
							int checkToIncrease3 = (int)y;
							y += yvel *(deltaTicks / 1000.f);
							if((int)y > checkToIncrease3)
								++yMiddle;
							break;
						}
					}
					break;
				}
			}
		}
		else
		{
			direction = 3;
			xvel = -pacmansSpeed;
			yvel = 0;
			int checkToIncrease = (int)x;
			x += xvel *(deltaTicks / 1000.f);
			if((int)x < checkToIncrease)
				--xMiddle;
		}
		break;
	case 0:
		switch(yMoveToo)
		{
		case -1:
			if(checkCollisionWithUpWall())
			{
				if(direction != 0)
				{
					switch(direction)
					{
					case 1:
						{
							if(!checkCollisionWithRightWall())
							{
								int checkToIncrease2 = (int)x;
								x += xvel *(deltaTicks / 1000.f);
								if((int)x > checkToIncrease2)
									++xMiddle;
								break;
							}
						}
						break;
					case 2:
						{
							if(!checkCollisionWithDownWall())
							{
								int checkToIncrease3 = (int)y;
								y += yvel *(deltaTicks / 1000.f);
								if((int)y > checkToIncrease3)
									++yMiddle;
								break;
							}
						}
						break;
					case 3:
						{
							if(!checkCollisionWithLeftWall())
							{
								int checkToIncrease3 = (int)x;
								x += xvel *(deltaTicks / 1000.f);
								if((int)x < checkToIncrease3)
									--xMiddle;
								break;
							}
						}
						break;
					}
				}
			}
			else
			{
				direction = 0;
				xvel = 0;
				yvel = -pacmansSpeed;
				int checkToIncrease = (int)y;
				y += yvel *(deltaTicks / 1000.f);
				if((int)y < checkToIncrease)
					--yMiddle;
			}
			break;
		case 1:
			if(checkCollisionWithDownWall())
			{
				if(direction != 2)
				{
					switch(direction)
					{
					case 0:
						{
							if(!checkCollisionWithUpWall())
							{
								int checkToIncrease1 = (int)y;
								y += yvel *(deltaTicks / 1000.f);
								if((int)y < checkToIncrease1)
									--yMiddle;
								break;
							}
						}
						break;
					case 1:
						{
							if(!checkCollisionWithRightWall())
							{
								int checkToIncrease2 = (int)x;
								x += xvel *(deltaTicks / 1000.f);
								if((int)x > checkToIncrease2)
									++xMiddle;
								break;
							}
						}
						break;
					case 3:
						{
							if(!checkCollisionWithLeftWall())
							{
								int checkToIncrease3 = (int)x;
								x += xvel *(deltaTicks / 1000.f);
								if((int)x < checkToIncrease3)
									--xMiddle;
								break;
							}
						}
						break;
					}
				}
			}
			else
			{
				direction = 2;
				xvel = 0;
				yvel = pacmansSpeed;
				int checkToIncrease = (int)y;
				y += yvel *(deltaTicks / 1000.f);
				if((int)y > checkToIncrease)
					++yMiddle;
			}
			break;
		}
		break;
	case 1:
		if(checkCollisionWithRightWall())
		{
			if(direction != 1)
			{
				switch(direction)
				{
				case 0:
					{
						if(!checkCollisionWithUpWall())
						{
							int checkToIncrease1 = (int)y;
							y += yvel *(deltaTicks / 1000.f);
							if((int)y < checkToIncrease1)
								--yMiddle;
							break;
						}
					}
					break;
				case 2:
					{
						if(!checkCollisionWithDownWall())
						{
							int checkToIncrease3 = (int)y;
							y += yvel *(deltaTicks / 1000.f);
							if((int)y > checkToIncrease3)
								++yMiddle;
							break;
						}
					}
					break;
				case 3:
					{	if(!checkCollisionWithLeftWall())
						{
							int checkToIncrease3 = (int)x;
							x += xvel *(deltaTicks / 1000.f);
							if((int)x < checkToIncrease3)
								--xMiddle;
							break;
						}
					}
					break;
				}
			}
		}
		else
		{
			direction = 1;
			xvel = pacmansSpeed;
			yvel = 0;
			int checkToIncrease = (int)x;
			x += xvel *(deltaTicks / 1000.f);
			if((int)x > checkToIncrease)
				++xMiddle;
		}
		break;
	}
}
void Pacman::handle_input()
{
	extern SDL_Event event;
	//If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
				if(checkCollisionWithUpWall())
				{
					xMoveToo = 0;
					yMoveToo = -1;
				}
				else
				{
					xvel = 0;
					yvel = -pacmansSpeed;
					xMoveToo = 0;
					yMoveToo = -1;
				}
				break;
            case SDLK_RIGHT:
				if(checkCollisionWithRightWall())
				{
					xMoveToo = 1;
					yMoveToo = 0;
				}
				else
				{
					xvel = pacmansSpeed;
					yvel = 0;
					xMoveToo = 1;
					yMoveToo = 0;
				}
				break;
			case SDLK_DOWN:
				if(checkCollisionWithDownWall())
				{
					xMoveToo = 0;
					yMoveToo = 1;
				}
				else
				{
					xvel = 0;
					yvel = pacmansSpeed;
					xMoveToo = 0;
					yMoveToo = 1;
				}
				break;
			case SDLK_LEFT:
				if(checkCollisionWithLeftWall())
				{
					xMoveToo = -1;
					yMoveToo = 0;
				}
				else
				{
					xvel = -pacmansSpeed;
					yvel = 0;
					xMoveToo = -1;
					yMoveToo = 0;
				}
				break;
            default:;
        }
    }
}