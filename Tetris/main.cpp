#include "Board.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

using namespace std;
const int SCREEN_HIGHT = 360;
const int SCREEN_WIDTH = 200;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;
SDL_Surface *natansBackground = NULL;
SDL_Surface *background = NULL;
SDL_Surface *halfCross = NULL;
SDL_Surface *cube = NULL;
SDL_Surface *stick = NULL;
SDL_Surface *stair1 = NULL;
SDL_Surface *stair2 = NULL;
SDL_Surface *l1 = NULL;
SDL_Surface *l2 = NULL;
SDL_Surface *background2 = NULL;
SDL_Surface *square = NULL;
SDL_Surface *blueCube = NULL;
SDL_Surface *brownCube = NULL;
SDL_Surface *greyCube = NULL;
SDL_Surface *redCube = NULL;
SDL_Surface *purpleCube = NULL;
SDL_Surface *yellowCube = NULL;
SDL_Surface *gameOver = NULL;
SDL_Surface *gameOverMessage = NULL;
TTF_Font *gameOverFont = NULL;
SDL_Color gameOverFontTextColor = { 0, 0, 0 };
SDL_Event event;

SDL_Rect sprite[4];
void clip()
{
    sprite[0].x = sprite[0].y = sprite[1].y = sprite[2].x = 0;
    sprite[1].x = sprite[2].y = sprite[3].x = sprite[3].y =
    sprite[0].w = sprite[0].h = sprite[1].w = sprite[1].h =
    sprite[2].w = sprite[2].h = sprite[3].w = sprite[3].h = 80;
}

void init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HIGHT,SCREEN_BPP,SDL_SWSURFACE | SDL_RESIZABLE);

	//Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }


    clip();
}
SDL_Surface *load_image(std::string filename)
{
    SDL_Surface *simpleSurface = NULL;
    SDL_Surface *optimizedSurface = NULL;
    simpleSurface = SDL_LoadBMP(filename.c_str());
    if(simpleSurface != NULL)
    {
        optimizedSurface = SDL_DisplayFormat(simpleSurface);
        SDL_FreeSurface(simpleSurface);
        if(optimizedSurface != NULL)
        {
            SDL_SetColorKey(optimizedSurface,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0x00,0xFF,0xFF));
        }
    }
    return optimizedSurface;
}
void load_files()
{
    background = load_image("images/background.bmp");
    background2 = load_image("images/background.bmp");
	natansBackground = load_image("images/the ++ company.bmp");
    halfCross = load_image("images/halfcross.bmp");
    cube = load_image("images/cube.bmp");
    stick = load_image("images/stick.bmp");
    stair1 = load_image("images/stair1.bmp");
    stair2 = load_image("images/stair2.bmp");
    l1 = load_image("images/l1.bmp");
    l2 = load_image("images/l2.bmp");
	square = load_image("images/square.bmp");
	blueCube = load_image("images/blueCube.bmp");
	brownCube = load_image("images/brownCube.bmp");
	greyCube = load_image("images/greyCube.bmp");
	redCube = load_image("images/redCube.bmp");
	purpleCube = load_image("images/purpleCube.bmp");
	yellowCube = load_image("images/yellowCube.bmp");
	gameOver = load_image("images/GameOver.bmp");
	//Open the font
    gameOverFont = TTF_OpenFont( "lazy.ttf", 28 );
    if(!background || !halfCross)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(2);
    }
	//If there was an error in loading the font
    if( gameOverFont == NULL )
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(2);
    }
    //SDL_SetAlpha( background, SDL_SRCALPHA, 150 );
}
void apply_surface(int x,int y,SDL_Surface *source,SDL_Surface *destination,SDL_Rect *clip = NULL)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source,clip,destination,&offset);
}
int main(int argv ,char *args[])
{
    init();
    load_files();
    Board tetris;
    apply_surface(0,0,background,screen);
	switch(tetris.shape)
    {
        case 0: apply_surface(tetris.x * 20,tetris.y*20,halfCross,screen,&sprite[tetris.state]);break;
        case 1: apply_surface(tetris.x * 20,tetris.y*20,cube,screen,&sprite[tetris.state]);break;
        case 2: apply_surface(tetris.x * 20,tetris.y*20,stick,screen,&sprite[tetris.state]);break;
        case 3: apply_surface(tetris.x * 20,tetris.y*20,stair1,screen,&sprite[tetris.state]);break;
        case 4: apply_surface(tetris.x * 20,tetris.y*20,stair2,screen,&sprite[tetris.state]);break;
        case 5: apply_surface(tetris.x * 20,tetris.y*20,l1,screen,&sprite[tetris.state]);break;
        case 6: apply_surface(tetris.x * 20,tetris.y*20,l2,screen,&sprite[tetris.state]);break;
        default:;
    }

    SDL_Flip(screen);

    bool quit = false;
	int timer = SDL_GetTicks();
	int timeToWaitUntilDropDown = -500;
	int nextLevel = 4;
    while(quit == false)
    {
        while(SDL_PollEvent( &event))
        {
            if(tetris.handleInput())
            {
                apply_surface(0,0,background,screen);
                switch(tetris.shape)
                {
                    case 0: apply_surface(tetris.x * 20,tetris.y*20,halfCross,screen,&sprite[tetris.state]);break;
                    case 1: apply_surface(tetris.x * 20,tetris.y*20,cube,screen,&sprite[tetris.state]);break;
                    case 2: apply_surface(tetris.x * 20,tetris.y*20,stick,screen,&sprite[tetris.state]);break;
                    case 3: apply_surface(tetris.x * 20,tetris.y*20,stair1,screen,&sprite[tetris.state]);break;
                    case 4: apply_surface(tetris.x * 20,tetris.y*20,stair2,screen,&sprite[tetris.state]);break;
                    case 5: apply_surface(tetris.x * 20,tetris.y*20,l1,screen,&sprite[tetris.state]);break;
                    case 6: apply_surface(tetris.x * 20,tetris.y*20,l2,screen,&sprite[tetris.state]);break;
                    default:;
                }
				for(int i = 0;i < 18;++i)
					for(int j=0;j < 10;++j)
						if(tetris.slots[i][j])
						{
							switch(tetris.slots[i][j].color)
							{
							case 0:
								apply_surface(j * 20, i * 20, square,screen);
								break;
							case 1:
								apply_surface(j * 20, i * 20, yellowCube,screen);
								break;
							case 2:
								apply_surface(j * 20, i * 20, purpleCube,screen);
								break;
							case 3:
								apply_surface(j * 20, i * 20, brownCube,screen);
								break;
							case 4:
								apply_surface(j * 20, i * 20, redCube,screen);
								break;
							case 5:
								apply_surface(j * 20, i * 20, greyCube,screen);
								break;
							case 6:
								apply_surface(j * 20, i * 20, blueCube,screen);
								break;
							}
						}
				SDL_Flip(screen);
            }

            if(event.type == SDL_QUIT)
                quit = true;
        }
		if(timer - SDL_GetTicks() < timeToWaitUntilDropDown)
		{
			tetris.goDown();
			timer = SDL_GetTicks();
			apply_surface(0,0,background,screen);
            switch(tetris.shape)
            {
                case 0: apply_surface(tetris.x * 20,tetris.y*20,halfCross,screen,&sprite[tetris.state]);break;
                case 1: apply_surface(tetris.x * 20,tetris.y*20,cube,screen,&sprite[tetris.state]);break;
                case 2: apply_surface(tetris.x * 20,tetris.y*20,stick,screen,&sprite[tetris.state]);break;
                case 3: apply_surface(tetris.x * 20,tetris.y*20,stair1,screen,&sprite[tetris.state]);break;
                case 4: apply_surface(tetris.x * 20,tetris.y*20,stair2,screen,&sprite[tetris.state]);break;
                case 5: apply_surface(tetris.x * 20,tetris.y*20,l1,screen,&sprite[tetris.state]);break;
                case 6: apply_surface(tetris.x * 20,tetris.y*20,l2,screen,&sprite[tetris.state]);break;
                default:;
            }
			for(int i = 0;i < 18;++i)
					for(int j=0;j < 10;++j)
						if(tetris.slots[i][j])
						{
							switch(tetris.slots[i][j].color)
							{
							case 0:
								apply_surface(j * 20, i * 20, square,screen);
								break;
							case 1:
								apply_surface(j * 20, i * 20, yellowCube,screen);
								break;
							case 2:
								apply_surface(j * 20, i * 20, purpleCube,screen);
								break;
							case 3:
								apply_surface(j * 20, i * 20, brownCube,screen);
								break;
							case 4:
								apply_surface(j * 20, i * 20, redCube,screen);
								break;
							case 5:
								apply_surface(j * 20, i * 20, greyCube,screen);
								break;
							case 6:
								apply_surface(j * 20, i * 20, blueCube,screen);
								break;
							}
						}
			SDL_Flip(screen);
			if(tetris.score > nextLevel)
			{
				timeToWaitUntilDropDown += 50;
				nextLevel +=5;
			}
		}
    }
    return 0;
}
