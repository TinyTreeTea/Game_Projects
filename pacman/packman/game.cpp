#include "game.h"
#include "SDL.h"
#include <string>
#include "pacman.h"
#include "ghost.h"

Game::~Game()
{
	SDL_FreeSurface(smallBall);
	SDL_FreeSurface(bigBall);
}
Game::Game()
{
	/*i know that this is a crude way to do this
	but i could not find any other way*/
	for(int j = 0;j < 26;++j)
		balls[0][j] = 1;
	balls[0][12] = 0;
	balls[0][13] = 0;

	for(int j = 0;j < 26;++j)
		balls[1][j] = 0;
	balls[1][0] = 1;
	balls[1][5] = 1;
	balls[1][11] = 1;
	balls[1][14] = 1;
	balls[1][20] = 1;
	balls[1][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[2][j] = 0;
	balls[2][0] = 2;
	balls[2][5] = 1;
	balls[2][11] = 1;
	balls[2][14] = 1;
	balls[2][20] = 1;
	balls[2][25] = 2;

	for(int j = 0;j < 26;++j)
		balls[3][j] = 0;
	balls[3][0] = 1;
	balls[3][5] = 1;
	balls[3][11] = 1;
	balls[3][14] = 1;
	balls[3][20] = 1;
	balls[3][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[4][j] = 1;

	for(int j = 0;j < 26;++j)
		balls[5][j] = 0;
	balls[5][0] = 1;
	balls[5][5] = 1;
	balls[5][8] = 1;
	balls[5][17] = 1;
	balls[5][20] = 1;
	balls[5][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[6][j] = 0;
	balls[6][0] = 1;
	balls[6][5] = 1;
	balls[6][8] = 1;
	balls[6][17] = 1;
	balls[6][20] = 1;
	balls[6][25] = 1;

	balls[7][0] = 1;
	balls[7][1] = 1;
	balls[7][2] = 1;
	balls[7][3] = 1;
	balls[7][4] = 1;
	balls[7][5] = 1;
	balls[7][6] = 0;
	balls[7][7] = 0;
	balls[7][8] = 1;
	balls[7][9] = 1;
	balls[7][10] = 1;
	balls[7][11] = 1;
	balls[7][12] = 0;
	balls[7][13] = 0;
	balls[7][14] = 1;
	balls[7][15] = 1;
	balls[7][16] = 1;
	balls[7][17] = 1;
	balls[7][18] = 0;
	balls[7][19] = 0;
	balls[7][20] = 1;
	balls[7][21] = 1;
	balls[7][22] = 1;
	balls[7][23] = 1;
	balls[7][24] = 1;
	balls[7][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[8][j] = 0;
	balls[8][5] = 1;
	balls[8][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[9][j] = 0;
	balls[9][5] = 1;
	balls[9][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[10][j] = 0;
	balls[10][5] = 1;
	balls[10][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[11][j] = 0;
	balls[11][5] = 1;
	balls[11][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[12][j] = 0;
	balls[12][5] = 1;
	balls[12][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[13][j] = 0;
	balls[13][5] = 1;
	balls[13][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[14][j] = 0;
	balls[14][5] = 1;
	balls[14][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[15][j] = 0;
	balls[15][5] = 1;
	balls[15][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[16][j] = 0;
	balls[16][5] = 1;
	balls[16][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[17][j] = 0;
	balls[17][5] = 1;
	balls[17][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[18][j] = 0;
	balls[18][5] = 1;
	balls[18][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[19][j] = 1;
	balls[19][12] = 0;
	balls[19][13] = 0;

	for(int j = 0;j < 26;++j)
		balls[20][j] = 0;
	balls[20][0] = 1;
	balls[20][5] = 1;
	balls[20][11] = 1;
	balls[20][14] = 1;
	balls[20][20] = 1;
	balls[20][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[21][j] = 0;
	balls[21][0] = 2;
	balls[21][5] = 1;
	balls[21][11] = 1;
	balls[21][14] = 1;
	balls[21][20] = 1;
	balls[21][25] = 2;

	for(int j = 0;j < 26;++j)
		balls[22][j] = 1;
	balls[22][3] = 0;
	balls[22][4] = 0;
	balls[22][21] = 0;
	balls[22][22] = 0;

	for(int j = 0;j < 26;++j)
		balls[23][j] = 0;
	balls[23][2] = 1;
	balls[23][5] = 1;
	balls[23][8] = 1;
	balls[23][17] = 1;
	balls[23][20] = 1;
	balls[23][23] = 1;

	for(int j = 0;j < 26;++j)
		balls[24][j] = 0;
	balls[24][2] = 1;
	balls[24][5] = 1;
	balls[24][8] = 1;
	balls[24][17] = 1;
	balls[24][20] = 1;
	balls[24][23] = 1;

	balls[25][0] = 1;
	balls[25][1] = 1;
	balls[25][2] = 1;
	balls[25][3] = 1;
	balls[25][4] = 1;
	balls[25][5] = 1;
	balls[25][6] = 0;
	balls[25][7] = 0;
	balls[25][8] = 1;
	balls[25][9] = 1;
	balls[25][10] = 1;
	balls[25][11] = 1;
	balls[25][12] = 0;
	balls[25][13] = 0;
	balls[25][14] = 1;
	balls[25][15] = 1;
	balls[25][16] = 1;
	balls[25][17] = 1;
	balls[25][18] = 0;
	balls[25][19] = 0;
	balls[25][20] = 1;
	balls[25][21] = 1;
	balls[25][22] = 1;
	balls[25][23] = 1;
	balls[25][24] = 1;
	balls[25][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[26][j] = 0;
	balls[26][0] = 1;
	balls[26][11] = 1;
	balls[26][14] = 1;
	balls[26][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[27][j] = 0;
	balls[27][0] = 1;
	balls[27][11] = 1;
	balls[27][14] = 1;
	balls[27][25] = 1;

	for(int j =0;j < 26;++j)
		balls[28][j] = 1;

	extern SDL_Surface *load_image( std::string filename );
	smallBall = load_image("images/ball.png");
	bigBall = load_image("images/bigBall.png");
}
void Game::resetBalls()
{
		/*i know that this is a crude way to do this
	but i could not find any other way*/
	for(int j = 0;j < 26;++j)
		balls[0][j] = 1;
	balls[0][12] = 0;
	balls[0][13] = 0;

	for(int j = 0;j < 26;++j)
		balls[1][j] = 0;
	balls[1][0] = 1;
	balls[1][5] = 1;
	balls[1][11] = 1;
	balls[1][14] = 1;
	balls[1][20] = 1;
	balls[1][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[2][j] = 0;
	balls[2][0] = 2;
	balls[2][5] = 1;
	balls[2][11] = 1;
	balls[2][14] = 1;
	balls[2][20] = 1;
	balls[2][25] = 2;

	for(int j = 0;j < 26;++j)
		balls[3][j] = 0;
	balls[3][0] = 1;
	balls[3][5] = 1;
	balls[3][11] = 1;
	balls[3][14] = 1;
	balls[3][20] = 1;
	balls[3][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[4][j] = 1;

	for(int j = 0;j < 26;++j)
		balls[5][j] = 0;
	balls[5][0] = 1;
	balls[5][5] = 1;
	balls[5][8] = 1;
	balls[5][17] = 1;
	balls[5][20] = 1;
	balls[5][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[6][j] = 0;
	balls[6][0] = 1;
	balls[6][5] = 1;
	balls[6][8] = 1;
	balls[6][17] = 1;
	balls[6][20] = 1;
	balls[6][25] = 1;

	balls[7][0] = 1;
	balls[7][1] = 1;
	balls[7][2] = 1;
	balls[7][3] = 1;
	balls[7][4] = 1;
	balls[7][5] = 1;
	balls[7][6] = 0;
	balls[7][7] = 0;
	balls[7][8] = 1;
	balls[7][9] = 1;
	balls[7][10] = 1;
	balls[7][11] = 1;
	balls[7][12] = 0;
	balls[7][13] = 0;
	balls[7][14] = 1;
	balls[7][15] = 1;
	balls[7][16] = 1;
	balls[7][17] = 1;
	balls[7][18] = 0;
	balls[7][19] = 0;
	balls[7][20] = 1;
	balls[7][21] = 1;
	balls[7][22] = 1;
	balls[7][23] = 1;
	balls[7][24] = 1;
	balls[7][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[8][j] = 0;
	balls[8][5] = 1;
	balls[8][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[9][j] = 0;
	balls[9][5] = 1;
	balls[9][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[10][j] = 0;
	balls[10][5] = 1;
	balls[10][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[11][j] = 0;
	balls[11][5] = 1;
	balls[11][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[12][j] = 0;
	balls[12][5] = 1;
	balls[12][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[13][j] = 0;
	balls[13][5] = 1;
	balls[13][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[14][j] = 0;
	balls[14][5] = 1;
	balls[14][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[15][j] = 0;
	balls[15][5] = 1;
	balls[15][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[16][j] = 0;
	balls[16][5] = 1;
	balls[16][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[17][j] = 0;
	balls[17][5] = 1;
	balls[17][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[18][j] = 0;
	balls[18][5] = 1;
	balls[18][20] = 1;

	for(int j = 0;j < 26;++j)
		balls[19][j] = 1;
	balls[19][12] = 0;
	balls[19][13] = 0;

	for(int j = 0;j < 26;++j)
		balls[20][j] = 0;
	balls[20][0] = 1;
	balls[20][5] = 1;
	balls[20][11] = 1;
	balls[20][14] = 1;
	balls[20][20] = 1;
	balls[20][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[21][j] = 0;
	balls[21][0] = 2;
	balls[21][5] = 1;
	balls[21][11] = 1;
	balls[21][14] = 1;
	balls[21][20] = 1;
	balls[21][25] = 2;

	for(int j = 0;j < 26;++j)
		balls[22][j] = 1;
	balls[22][3] = 0;
	balls[22][4] = 0;
	balls[22][21] = 0;
	balls[22][22] = 0;

	for(int j = 0;j < 26;++j)
		balls[23][j] = 0;
	balls[23][2] = 1;
	balls[23][5] = 1;
	balls[23][8] = 1;
	balls[23][17] = 1;
	balls[23][20] = 1;
	balls[23][23] = 1;

	for(int j = 0;j < 26;++j)
		balls[24][j] = 0;
	balls[24][2] = 1;
	balls[24][5] = 1;
	balls[24][8] = 1;
	balls[24][17] = 1;
	balls[24][20] = 1;
	balls[24][23] = 1;

	balls[25][0] = 1;
	balls[25][1] = 1;
	balls[25][2] = 1;
	balls[25][3] = 1;
	balls[25][4] = 1;
	balls[25][5] = 1;
	balls[25][6] = 0;
	balls[25][7] = 0;
	balls[25][8] = 1;
	balls[25][9] = 1;
	balls[25][10] = 1;
	balls[25][11] = 1;
	balls[25][12] = 0;
	balls[25][13] = 0;
	balls[25][14] = 1;
	balls[25][15] = 1;
	balls[25][16] = 1;
	balls[25][17] = 1;
	balls[25][18] = 0;
	balls[25][19] = 0;
	balls[25][20] = 1;
	balls[25][21] = 1;
	balls[25][22] = 1;
	balls[25][23] = 1;
	balls[25][24] = 1;
	balls[25][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[26][j] = 0;
	balls[26][0] = 1;
	balls[26][11] = 1;
	balls[26][14] = 1;
	balls[26][25] = 1;

	for(int j = 0;j < 26;++j)
		balls[27][j] = 0;
	balls[27][0] = 1;
	balls[27][11] = 1;
	balls[27][14] = 1;
	balls[27][25] = 1;

	for(int j =0;j < 26;++j)
		balls[28][j] = 1;
}
bool Game::applyBalls(Pacman &pacman,Ghost ghost[])
{
	extern Uint32* get_pixel32( SDL_Surface *surface, int x, int y );
	extern SDL_Surface *screen;
	extern void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
	extern bool breakLoop;
	bool noBallLeft = true;
	bool isPacmanOnBall = false;
	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);
	for(int i = 0;i < 29;++i)
	{
		for(int j = 0;j < 26;++j)
		{
			if(balls[i][j] > 0)
			{
				noBallLeft = false;
				Uint8 *checkCollision = (Uint8 *)get_pixel32(screen, (j + 1) * (398 / 26) + 95, (i + 1) * (391 / 29) + 16);
				if(checkCollision[1] > 250 && checkCollision[2] > 250)
				{
					isPacmanOnBall = true;
					pacman.score += 10;
					if(balls[i][j] == 2)
						for(int i = 0;i < 4;++i)
							if(ghost[i].state == 2 || ghost[i].state == 3)
							{
								pacman.bonusEatingScore = 0;
								ghost[i].timer.start();
								ghost[i].state = 3;
							}
					balls[i][j] = 0;
				}
				else if(balls[i][j] == 1)
					apply_surface((j + 1) * (398 / 26) + 95, (i + 1) * (391 / 29) + 16, smallBall, screen);
				else
					apply_surface(((j + 1) * (398 / 26) + 95) - 5, ((i + 1) * (391 / 29) + 16) - 5, bigBall, screen);
			}
		}
	}
	if(SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);
	if(noBallLeft)
	{
		breakLoop = noBallLeft;
		resetBalls();
	}
	return isPacmanOnBall;
}