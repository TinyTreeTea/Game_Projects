#include "LazyFooFunctionsAndConstants.h"
#include "Globals.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <iostream>
#include "Survival.h"
#include <fstream>
#include "ZombieKiller.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include "GameOver.h"

SDL_Surface *load_image( std::string filename, bool colorKey)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL)
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if(optimizedImage != NULL && colorKey)
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }

		//if there was a problem in loading the optimizedImage
		else if(optimizedImage == NULL)
		{
			//get the last error occured
			std::cerr << SDL_GetError << "\n";

			exit(1);
		}
    }

	//if there was a problem in loading the image
	else
	{
		//get the last error occured
		std::cerr << SDL_GetError << "\n";

		exit(1);
	}

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

//My Surface blitter
void my_apply_surface(int x,int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	if(x >= destination->w || y >= destination->h)
		return;
	if(clip != NULL)
		if(x + clip->w < 0 || y + clip->y < 0)
			return;
	//if the picture has a color key
	if(source->flags == 4096)
	{
		if(clip == NULL)
		{
			for(int i = 0;i < source->h;++i)
			{
				for(int j = 0;j < source->w;++j)
				{
					Uint32 pixel = getpixel(source,j,i);
					if(pixel != source->format->colorkey)
					{
						if(j + x >= 0 && j + x < destination->w && i + y >= 0 && i + y < destination->h)
							putpixel(destination, j + x, i + y, pixel);
					}
				}
			}
		}
		else
		{
			for(int i = clip->y;i < clip->y + clip->h;++i)
			{
				for(int j = clip->x;j < clip->x + clip->w;++j)
				{
					Uint32 pixel = getpixel(source,j,i);
					if(pixel != source->format->colorkey)
					{
						if(j - clip->x  + x >= 0 && j - clip->x  + x < destination->w && 
							i - clip->y + y >= 0 && i - clip->y + y < destination->h)
							putpixel(destination, j - clip->x + x, i - clip->y + y, pixel);
					}
				}
			}
		}
	}
	else
	{
		if(clip == NULL)
		{
			for(int i = 0;i < source->h;++i)
			{
				for(int j = 0;j < source->w;++j)
				{
					Uint32 pixel = getpixel(source,j,i);
					if(j + x >= 0 && j + x < destination->w && i + y >= 0 && i + y < destination->h)
						putpixel(destination, j + x, i + y, pixel);
				}
			}
		}
		else
		{
			for(int i = clip->y;i < clip->y + clip->h;++i)
			{
				for(int j = clip->x;j < clip->x + clip->w;++j)
				{
					Uint32 pixel = getpixel(source,j,i);
					if(j - clip->x  + x >= 0 && j - clip->x  + x < destination->w && 
							i - clip->y + y >= 0 && i - clip->y + y < destination->h)
							putpixel(destination, j - clip->x + x, i - clip->y + y, pixel);
				}
			}
		}
	}
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
		std::cerr << SDL_GetError() << "\n";
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
		std::cerr << SDL_GetError() << "\n";
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN);

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
		std::cerr << SDL_GetError() << "\n";
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Rotation", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 36 );

	zombieKillerSurfaceSpriteSheet = load_image("Images/ZombieKillerSpriteSheet.bmp",true);
	zombieKillerSurfaceSpriteSheet1 = load_image("Images/ZombieKillerSpriteSheet1.bmp",true);
	zombieKillerSurfaceSpriteSheet2 = load_image("Images/ZombieKillerSpriteSheet2.bmp",true);
	zombieKillerSurfaceSpriteSheet3 = load_image("Images/ZombieKillerSpriteSheet3.bmp",true);
	zombieKillerSurfaceSpriteSheet4 = load_image("Images/ZombieKillerSpriteSheet4.bmp",true);
	zombieKillerSurfaceSpriteSheet5 = load_image("Images/ZombieKillerSpriteSheet5.bmp",true);
	zombieKillerSurfaceSpriteSheetMinus1 = load_image("Images/ZombieKillerSpriteSheetMinus1.bmp",true);
	zombieKillerSurfaceSpriteSheetMinus2 = load_image("Images/ZombieKillerSpriteSheetMinus2.bmp",true);
	zombieKillerSurfaceSpriteSheetMinus3 = load_image("Images/ZombieKillerSpriteSheetMinus3.bmp",true);
	zombieKillerSurfaceSpriteSheetMinus4 = load_image("Images/ZombieKillerSpriteSheetMinus4.bmp",true);
	zombieKillerSurfaceSpriteSheetMinus5 = load_image("Images/ZombieKillerSpriteSheetMinus5.bmp",true);
	sparksSpriteSheet = load_image("Images/sparksSpriteSheet.bmp",true);
	bulletSpriteSheet = load_image("Images/bulletSpriteSheet.bmp",true);
	zombieSpriteSheet = load_image("Images/zombieSpriteSheet.bmp",true);
	bloodSpriteSheet = load_image("Images/bloodSpriteSheet.bmp",true);
	deadSpriteSheet = load_image("Images/deadSpriteSheet.bmp",true);
	background = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY,LEVEL_WIDTH,LEVEL_HEIGHT,24,0xff0000,0xff00,0xff,0);
	SDL_FillRect(background,NULL,SDL_MapRGB(background->format,0,255,255));
	SDL_SetColorKey(background,SDL_SRCCOLORKEY,SDL_MapRGB(background->format,0,255,255));

	std::ifstream zombieKillerClipFile("Clips/ZombieKillerClip");
	if(zombieKillerClipFile == NULL)
	{
		std::cerr << SDL_GetError() << "\n";
		return false;
	}
	zombieKillerClipFile >> zombieKillerClipLength;
	zombieKillerClip = new SDL_Rect[zombieKillerClipLength];
	int width, height;
	zombieKillerClipFile >> width;
	zombieKillerClipFile >> height;
	for(int i = 0;i < zombieKillerClipLength;++i)
	{
		zombieKillerClip[i].w = width;
		zombieKillerClip[i].h = height;
		zombieKillerClipFile >> zombieKillerClip[i].x;
		zombieKillerClipFile >> zombieKillerClip[i].y;
	}

	zombieKillerClipFile.close();
	std::ifstream sparksClipFile("Clips/sparksClip");
	int sparksClipLength, width2, height2;
	sparksClipFile >> sparksClipLength;
	sparksClipFile >> width2;
	sparksClipFile >> height2;

	zombieInformation = new Information[zombieKillerClipLength];
	std::ifstream bulletClipFile("Clips/bulletClip");
	int bulletLength,width3,height3;
	bulletClipFile >> bulletLength >> width3 >> height3;

	std::ifstream zombieClipFile("Clips/zombieClip");
	int zombieClipLength, width4, height4;
	zombieClipFile >> zombieClipLength >> width4 >> height4;

	std::ifstream bloodClipFile("Clips/bloodClip");
	int bloodClipLength, width5, height5;
	bloodClipFile >> bloodClipLength >> width5 >> height5;

	std::ifstream deadClipFile("Clips/deadClip");
	int deadClipLength, width6, height6;
	deadClipFile >> deadClipLength >> width6 >> height6;

	for(int i=0; i< zombieKillerClipLength; ++i)
	{
		zombieInformation[i].clip6.w = width6;
		zombieInformation[i].clip6.h = height6;
		deadClipFile >> zombieInformation[i].clip6.x >> zombieInformation[i].clip6.y;
		zombieInformation[i].clip5.w = width5;
		zombieInformation[i].clip5.h = height5;
		bloodClipFile >> zombieInformation[i].clip5.x >> zombieInformation[i].clip5.y;
		zombieInformation[i].clip4.w = width4;
		zombieInformation[i].clip4.h = height4;
		zombieClipFile >> zombieInformation[i].clip4.x >> zombieInformation[i].clip4.y;
		zombieInformation[i].clip3.w = width3;
		zombieInformation[i].clip3.h = height3;
		bulletClipFile >> zombieInformation[i].clip3.x >> zombieInformation[i].clip3.y;
		zombieInformation[i].clip2.w = width2;
		zombieInformation[i].clip2.h = height2;
		sparksClipFile >> zombieInformation[i].clip2.x;
		sparksClipFile >> zombieInformation[i].clip2.y;
		zombieInformation[i].clip = zombieKillerClip[i];
		zombieInformation[i].angle = ((360+0.0)/zombieKillerClipLength)*i;
	}
	sparksClipFile.close();
	bulletClipFile.close();
	zombieClipFile.close();
	bloodClipFile.close();



	//find the tip of the gun in the first clip in the sprite sheet ASSUMING that the tip is at the northest untransparent point.
	Uint32 colorKey = SDL_MapRGB(zombieKillerSurfaceSpriteSheet->format,0x00,0xFF,0xFF);
	Uint32 * runner = (Uint32*)zombieKillerSurfaceSpriteSheet->pixels;
	int newX=0, newY=0;
	for(newY=0; newY<height; ++newY)
		for(newX=0; newX<width; ++newX)		
			if(runner[newY*zombieKillerSurfaceSpriteSheet->w + newX] != colorKey)
				goto end;
end:
	double distance = sqrt((newX - (width+0.0)/2)*(newX - (width+0.0)/2) + (newY - (height+0.0)/2)*(newY - (height+0.0)/2));
	double currentAngle = acos((newX - (width+0.0)/2)/distance);
	double deltaAngle = 6.2831853/zombieKillerClipLength;

	for(int i=0; i< zombieKillerClipLength; ++i)
	{
		zombieInformation[i].xTipOfGun = (int)((width+0.0)/2 + (cos(currentAngle) * distance));
		zombieInformation[i].yTipOfGun = (int)((height+0.0)/2 - (sin(currentAngle) * distance));
		currentAngle += deltaAngle;
	}


	//loading the spawn data from the file
	std::ifstream spawn("SpawnData/spawn");
	SpawnData ** runner2 = &spawndata;
	int time;
	spawn >> time;
	while(time != -1)
	{
		(*runner2) = new SpawnData(time,*runner2);
		runner2 = &((*runner2)->next);
		spawn >> time;
	}
	spawn.close();


		

    //If there was an error in loading the font
    if( font == NULL )
    {
		std::cerr << SDL_GetError() << "\n";
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Delete game state and free state resources
    delete currentState;

	//delete surfaces in Globals.cpp
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheet);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheet1);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheet2);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheet3);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheet4);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheet5);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheetMinus1);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheetMinus2);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheetMinus3);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheetMinus4);
	SDL_FreeSurface(zombieKillerSurfaceSpriteSheetMinus5);
	delete [] zombieKillerClip;
	delete [] zombieInformation;

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void set_next_state(int newState)
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

void change_state()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        //Change the state
        switch( nextState )
        {
		/*case STATE_INTRO:
			currentState = new Intro();
			break;*/
		case STATE_SURVIVAL:
			currentState = new Survival();
			break;
		case STATE_GAME_OVER:
			currentState = new GameOver();
			break;
        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
    }
}
Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;
    
	//Get the requested pixel
	return pixels[ ( y * surface->w ) + x ];
}
/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


//returns the radian angle between spot1 to spot2, starting from 12 oclock and going counter clockwise.
double calculateRadianAngle(int x1, int y1, int x2, int y2)
{
	int deltaX = x1-x2, deltaY = y1-y2;	
	double distance = sqrt(deltaX*deltaX+deltaY*deltaY+0.0);
	double radianAngle;
	if(deltaY>=0)
		radianAngle = acos((deltaX+0.0)/distance);
	else if(deltaY<0 && deltaX>=0)
		radianAngle = asin((deltaY+0.0)/distance);
	else
		radianAngle = 6.2831853 - acos((deltaX+0.0)/distance);

	radianAngle = 6.2831853 - radianAngle - 1.5707963;

	return radianAngle;
}

void pixel::extract()
{
	Uint8 * p = (Uint8*)&color;
	b = p[0];
	g = p[1];
	r = p[2];
	a = p[3];
}

void pixel::update()
{
	Uint8 * p = (Uint8*)&color;
	p[0] = b;
	p[1] = g;
	p[2] = r;
	p[3] = a;
}



SDL_Surface * Grid::createSpreadSheet(int centerHeight, int centerWidth)
{
	int deltaX = 0, deltaY = 0;
	
	for(double l=0; l<360; l+= (360+0.0)/MODERATION)
	{
		updateGrid();
		rotate(l,centerHeight,centerWidth);
		for(int i=0; i<h; ++i)
			for(int j=0; j<w; ++j)
				if(grid[i][j].color != 0xFF00FFFF)
				{
					//std::cout << "color is: " << grid[i][j].color << "   coordinates: " << i << ',' << j << '\n';
					if(deltaY < centerHeight-i)
						deltaY = centerHeight-i;
					i = h;
					j = w;
				}
		for(int i=h-1; i>=0; --i)
			for(int j=0; j<w; ++j)
				if(grid[i][j].color != 0xFF00FFFF)
				{
					if(deltaY < i-centerHeight)
						deltaY = i-centerHeight;
					i = -1;
					j = w;
				}
		for(int j=0; j<w; ++j)
			for(int i=0; i<h; ++i)
				if(grid[i][j].color != 0xFF00FFFF)
				{
					if(deltaX < centerWidth-j)
						deltaX = centerWidth-j;
					i = h;
					j = w;
				}
		for(int j=w-1; j>=0; --j)
			for(int i=0; i<h; ++i)
				if(grid[i][j].color != 0xFF00FFFF)
				{
					if(deltaX < j-centerWidth)
						deltaX = j-centerWidth;
					j = -1;
					i = h;
				}
	}

	std::cout << "deltaX: " << deltaX << "   deltaY: " << deltaY << '\n';

	int beginHeight = centerHeight - deltaY;
	int beginWidth = centerWidth - deltaX;		//the rectangle data, of the spreadsheet.
	int newHeight = deltaY*2+1;
	int newWidth = deltaX*2+1;
	int dim = sqrt(MODERATION+0.0);
	
	SDL_Surface * p = SDL_CreateRGBSurface(SDL_SWSURFACE,newWidth*dim,newHeight*dim,SCREEN_BPP,0xFF0000,0xFF00,0xFF,0xFF000000);
	if(!p)
	{
		std::cout<< SDL_GetError() << '\n';
		exit(100);
	}
	
	Grid spreadSheet(p);


	double rotate2 = (360+0.0)/MODERATION;
	int i=0,l=0;
	while(l*dim+i<MODERATION)
	{
		updateGrid();
		rotate((l*dim+i)*rotate2,centerHeight,centerWidth);
		for(int j=0; j<newHeight; ++j)
			for(int k=0; k<newWidth; ++k)
				spreadSheet.grid[l*newHeight+j][i*newWidth+k] = grid[beginHeight+j][beginWidth+k];
		if(i<dim-1)
			++i;
		else{
			++l; 
			i = 0;
		}
			
	}
	spreadSheet.updateSource();



	return p;	
}

void Grid::rotate(double angle,int centerHeight, int centerWidth)
{
	double rotate = angle*asin(1.0)*2/180;											//the angle is considered clockwise.
	double midHeight = centerHeight;
	double midWidth = centerWidth;
	double distance = sqrt((midHeight-0.5)*(midHeight-0.5) + (midWidth-0.5)*(midWidth-0.5));	//from the (0.5,0.5);
	double angle2 = asin((midHeight-0.5)/distance) + rotate + asin(1.0)*2;			//angle between the vectors (midHeight,0) and (0.5,0.5) from the midpoint.
	double newX = (cos(angle2)*distance + midWidth);
	double newY = (sin(angle2)*distance + midHeight);

	pixel ** tmpGrid = new pixel*[h];
	for(int i=0; i<h; ++i)
		tmpGrid[i] = new pixel[w];
	double x = newX, y = newY;
	double sinAngle = sin(rotate);
	double cosAngle = cos(rotate);
	double x2, y2;
	for(int i=0; i<h; ++i)
	{
		x2 = x; 
		y2 = y;
		for(int j=0; j<w; ++j)
		{
			if(x2>=0 && x2<=w && y2>=0 && y2<=h)
				tmpGrid[i][j] = grid[(int)y2][(int)x2];
			else{
				tmpGrid[i][j].a = tmpGrid[i][j].b = tmpGrid[i][j].g = 255;
				tmpGrid[i][j].r = 0;
				tmpGrid[i][j].update();
			}
			x2 += cosAngle;
			y2 += sinAngle;
		}
		x -= sinAngle;
		y += cosAngle;
	}

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			grid[i][j] = tmpGrid[i][j];


	
	//std::cout << "\n\nthe new point coordiantes are: " << newY << ',' << newX << '\n';
	//std::cout << "rotate: " << rotate << "   distance: " << distance << "  angle2: " << angle2 << '\n';
	


	for(int i=0; i<h; ++i)
		delete [] tmpGrid[i];
	delete [] tmpGrid;


}

void Grid::noRed()
{
	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
		{
			grid[i][j].r = 0;
			grid[i][j].update();
		}
}

void Grid::alpha()
{
	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
		{
			grid[i][j].a = 255;
			grid[i][j].update();
		}
}

Grid::Grid(SDL_Surface * sourceSurface):destination(NULL)
{
	std::cout << "creating a Grid\n";
	source = sourceSurface;
	w = source->w;
	h = source->h;
	grid = new pixel*[h];
	for(int i=0; i<h; ++i)
		grid[i] = new pixel[w];
	updateGrid();
	alpha();
}

void Grid::updateGrid()
{
	lock(source);

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
		{
			grid[i][j].color = getPixel(j,i);
			grid[i][j].extract();
		}
	unlock(source);

	alpha();
}

void Grid::updateDestination()
{
	if(!destination)
		return;
	lock( destination );
	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
		{
			grid[i][j].update();
			putPixel(j,i,grid[i][j].color);		
		}
	unlock( destination );
}

void Grid::updateSource()
{
	SDL_Surface * tmp = destination;		//swap source with destination and perform an update destination.
	destination = source;
	updateDestination();
	destination = tmp;
}

SDL_Surface * Grid::createDestination()
{
	SDL_Surface * p = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,SCREEN_BPP,0xFF0000,0xFF00,0xFF,0xFF000000);
	destination = p;
	updateDestination();
	return p;
}

Uint32 Grid::getPixel(int x, int y)
{
	int bpp = source->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)source->pixels + y * source->pitch + x * bpp;
	switch(bpp) 
	{
		case 1:
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)			
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
		case 4:
			return *(Uint32 *)p;
		default:
			return 0; /* shouldn’t happen, but avoids warnings */
	}
}

void Grid::putPixel(int x, int y, Uint32 pixel)
{
	int bpp = destination->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)destination->pixels + y * destination->pitch + x * bpp;
		switch(bpp) 
		{
			case 1:
				*p = pixel;
				break;
			case 2:
				*(Uint16 *)p = pixel;
				break;
			case 3:
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
				{  //this case can potentially be excluded
					p[0] = (pixel >> 16) & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = pixel & 0xff;
				} 
				else 
				{
					p[0] = pixel & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = (pixel >> 16) & 0xff;
				}	
				break;
			case 4:
				*(Uint32 *)p = pixel;
				break;
		}
}

void Grid::lock(SDL_Surface * surface)
{
	if(SDL_MUSTLOCK(surface))
		if(SDL_LockSurface(surface)<0)
		{
			std::cout << "failed locking surface: " << SDL_GetError() << '\n';
			exit(100);
		}
}

void Grid::unlock(SDL_Surface * surface)
{
	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}

Grid::~Grid()
{
	for(int i=0; i<h; ++i)
		delete [] grid[i];
	delete [] grid;
}

SDL_Surface *scaleSurface(SDL_Surface *surface, double scaleWidth, double scaleHeight)
{
	/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    SDL_Surface *scaledSurfaceByWidth2;
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	scaledSurfaceByWidth2 = SDL_CreateRGBSurface(SDL_SWSURFACE, (int)(scaleWidth * surface->w),
		surface->h, 32, rmask, gmask, bmask, amask);

	SDL_Surface *scaledSurfaceByWidth = SDL_DisplayFormat(scaledSurfaceByWidth2);

	SDL_FreeSurface(scaledSurfaceByWidth2);

	double untilWidth = scaleWidth, untilHeight = scaleHeight;

	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
	if(SDL_MUSTLOCK(scaledSurfaceByWidth))
		SDL_LockSurface(scaledSurfaceByWidth);

	//stretch picture by width
	for(int y = 0;y < surface->h;++y)
	{
		for(int x = 0;x < surface->w;++x)
		{
			for(int from = (int)(untilWidth - scaleWidth);from <= (int)untilWidth - 1;++from)
			{
				putpixel(scaledSurfaceByWidth,from,y,getpixel(surface,x,y));
			}
			untilWidth += scaleWidth;
		}
		untilWidth = scaleWidth;
	}

	/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    SDL_Surface *scaledSurface2;

	scaledSurface2 = SDL_CreateRGBSurface(SDL_SWSURFACE, (int)(scaleWidth * surface->w),
		(int)(scaleHeight * surface->h), 32, rmask, gmask, bmask, amask);

	SDL_Surface *scaledSurface = SDL_DisplayFormat(scaledSurface2);

	SDL_FreeSurface(scaledSurface2);

	if(SDL_MUSTLOCK(scaledSurface))
		SDL_LockSurface(scaledSurface);

	//strech picture by height
	for(int x = 0;x < scaledSurfaceByWidth->w;++x)
	{
		for(int y = 0;y < scaledSurfaceByWidth->h;++y)
		{
			for(int from = (int)(untilHeight - scaleHeight);from <= (int)untilHeight - 1;++from)
			{
				putpixel(scaledSurface,x,from,getpixel(scaledSurfaceByWidth,x,y));
			}
			untilHeight += scaleHeight;
		}
		untilHeight = scaleHeight;
	}

	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	if(SDL_MUSTLOCK(scaledSurfaceByWidth))
		SDL_UnlockSurface(scaledSurfaceByWidth);
	if(SDL_MUSTLOCK(scaledSurface))
		SDL_UnlockSurface(scaledSurface);

	SDL_FreeSurface(scaledSurfaceByWidth);

	return scaledSurface;
}

void Grid::saveSpriteSheetAndSaveClip(SDL_Surface *surface, int centerHeight, int centerWidth
	, std::string spriteSheetFileName, std::string clipFileName)
{
	surface = createSpreadSheet(centerHeight,centerWidth);
	SDL_SaveBMP(surface,spriteSheetFileName.c_str());
	toClip(surface);

	//Open a file for writing
    std::ofstream save(clipFileName);

	save << MODERATION << " ";
	save << clip->w << " ";
	save << clip->h << " ";
	for(int i = 0;i < MODERATION;++i)
		save << clip[i].x << " " << clip[i].y << " ";
}

void toClip(SDL_Surface * surface)
{
	int dim = sqrt(MODERATION+0.0);
	int height = surface->h/dim;
	int width = surface->w/dim;
	for(int i=0; i<MODERATION; ++i)
	{
		clip[i].h = height;
		clip[i].w = width;
	}
	int i=0,j=0;
	while(j*dim+i < MODERATION)
	{
		clip[j*dim+i].x = i*width;
		clip[j*dim+i].y = j*height;
		if(i<dim-1)
			++i;
		else
		{
			++j;
			i = 0;
		}

	}

}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

std::string intToString(int n)
{
	std::ostringstream result;
	result << n;
	return result.str();
}
