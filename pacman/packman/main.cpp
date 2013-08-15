#include "SDL.h"
#include "SDL_image.h"
#include "pacman.h"
#include <string>
#include "game.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include "ghost.h"
#include <time.h>
#include "timer.h"
#include <fstream>

SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
//The font that's going to be used
TTF_Font *score = NULL;
//The color of the font
SDL_Color textColor = { 255, 255, 255 };
SDL_Event event;
bool breakLoop = false;

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
			if(filename != "images/background.png")
				SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0 ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

		//Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Pacman", NULL );

	screen = SDL_SetVideoMode(600,450,32,0);

    //If eveything loads fine
    return true;
}

bool load_files(int &highscore)
{
    //Load the image
    background = load_image( "images/background.png" );

	//Open the font
    score = TTF_OpenFont( "font.ttf", 28 );

    //If the image didn't load
    if( background == NULL )
    {
        return false;
    }

	//Open a file for reading
    std::ifstream load( "game_save" );

	if(load != NULL)
	{
		int offset;
		load >> offset;
		highscore = offset;
		load.close();
	}

    //If eveything loaded fine
    return true;
}
void clean_up(Pacman &pacman,int highscore)
{
	//Open a file for writing
	if(highscore < pacman.score)
	{
		std::ofstream save( "game_save" );
		save << pacman.score;
		save.close();
	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
	TTF_CloseFont(score);
	TTF_Quit();
	SDL_Quit();
}
int main(int args, char *argv[])
{
	if(!init())
		return 1;
	int highscore;
	if(!load_files(highscore))
		return 2;
	std::srand(time(NULL));//to use rand in the program
	apply_surface(0,0,background,screen);
	SDL_Flip(screen);
	bool quit = false;
	Pacman pacman;
	Game game;
	Timer delta,ghostDelta;
	ghostDelta.start();
	delta.start();
	bool isMouthOpen = true;
	int counter = 0;
	int ghostSpeed = 85;
	Ghost ghost[4] = 
	{
		Ghost(299,161,load_image("images/redGhost.png"),ghostSpeed,2),
	    Ghost(268,207,load_image("images/pinkGhost.png"),ghostSpeed,0,20),
		Ghost(299,207,load_image("images/orangeGhost.png"),ghostSpeed,0,10),
		Ghost(328,207,load_image("images/lightBlueGhost.png"),ghostSpeed,0,30)
	};
	while(!quit)
	{
		do
		{
			while( SDL_PollEvent( &event ) )
			{
				if(event.type == SDL_QUIT)
					quit = true;
				pacman.handle_input();
			}
			apply_surface(0,0,background,screen);
			pacman.move(delta.get_ticks());
			for(int i = 0;i < 4;++i)
				ghost[i].move(ghostDelta.get_ticks(),pacman,ghost);
			ghostDelta.start();
			delta.start();
			pacman.show(isMouthOpen);
			if(isMouthOpen)
				isMouthOpen = !game.applyBalls(pacman,ghost);
			else if(counter % 70 == 0)
			{
				++counter;
				isMouthOpen = !game.applyBalls(pacman,ghost);
			}
			else
			{
				game.applyBalls(pacman,ghost);
				++counter;
			}
			for(int i = 0;i < 4;++i)
				ghost[i].show();
			char buffer[10];
			buffer[9] = '/n';
			SDL_Surface *temp = TTF_RenderText_Solid( score, itoa(pacman.score,buffer,10), textColor);
			apply_surface(5,60,temp,screen);
			SDL_FreeSurface(temp);
			temp = TTF_RenderText_Solid( score, itoa(highscore,buffer,10), textColor );
			apply_surface(510,60,temp,screen);
			SDL_FreeSurface(temp);
			if((int)pacman.x != pacman.xMiddle - 12.0 || (int)pacman.y != pacman.yMiddle - 12.0)
			{
				pacman.x = pacman.xMiddle - 12.0;
				pacman.y = pacman.yMiddle - 12.0;
				for(int i = 0;i < 4;++i)
				{
					ghost[i].x = ghost[i].xMiddle - 12.0;
					ghost[i].y = ghost[i].yMiddle - 12.0;
				}
			}
			SDL_Flip(screen);
		}while(!breakLoop && !quit);
		if(quit)
			break;
		breakLoop = false;
		if(pacman.lives == 0)
			break;
		pacman.pacmanReset(pacman.score,pacman.lives);
		ghostSpeed += 2;
		isMouthOpen = true;
		counter = 0;
		ghost[0].ghostReset(299,161,ghostSpeed,2);
		ghost[1].ghostReset(268,207,ghostSpeed,0,20);
		ghost[2].ghostReset(299,207,ghostSpeed,0,10);
		ghost[3].ghostReset(328,207,ghostSpeed,0,30);
		SDL_Delay(1000);
		ghostDelta.start();
		delta.start();
	}
	clean_up(pacman,highscore);
	return 0;
}