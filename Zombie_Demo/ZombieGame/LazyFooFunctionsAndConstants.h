#ifndef LAZYFUNCTIONSANDCONSTANTS_H_INCLUDED
#define LAZYFUNCTIONSANDCONSTANTS_H_INCLUDED

//The headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

/*Constants*/
//Screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;
const int SCREEN_BPP = 32;

//The dimensions of the level
const int LEVEL_WIDTH = 4000;
const int LEVEL_HEIGHT = 4000;

//The frame rate
const int FRAMES_PER_SECOND = 110;

//the number of rotation twists
const int MODERATION = 64;

//Game states
enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_SURVIVAL,
    STATE_GAME_OVER,
    STATE_EXIT
};

/*Functions*/
//Image loader
SDL_Surface *load_image( std::string filename, bool colorKey = false);

//Surface blitter
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

//My Surface blitter
void my_apply_surface(int x,int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

//Initialization
bool init();

//File loading
bool load_files();

//Clean up
void clean_up();

//State status manager
void set_next_state( int newState );

//State changer
void change_state();

//get the pixel
Uint32 get_pixel32( SDL_Surface *surface, int x, int y );

//copys the surface into a grid and returns the grid.NOTE: dont forget to delete the grid!!
int **SurfaceToGrid(SDL_Surface *surface);

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y);

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

/*scales the "surface" according to the "scale" that you send it for example:
  if scale is 2 then the surface will double its size.
  returns a new surface and doesn't erase the old one*/
SDL_Surface *scaleSurface(SDL_Surface *surface, double scaleWidth, double scaleHeight);

double calculateRadianAngle(int x1, int y1, int x2, int y2);

struct pixel
{
	Uint8 r,g,b,a;
	Uint32 color;//mask should be a,r,g,b;
	pixel():color(0),r(0),g(0),b(0),a(0){}
	void extract();
	void update();
};

class Grid
{
private:
	int w,h;
	SDL_Surface * source;
	SDL_Surface * destination;
	void putPixel(int x, int y, Uint32 pixel);
	Uint32 getPixel(int x, int y);
public:
	pixel ** grid;
	Grid(SDL_Surface * source);
	void updateGrid();
	void updateDestination();
	void updateSource();
	void noRed();
	void alpha();
	void rotate(double angle,int centerHeight = SCREEN_HEIGHT / 2, int centerWidth = SCREEN_WIDTH / 2);
	SDL_Surface * createSpreadSheet(int centerHeight, int centerWidth);
	void saveSpriteSheetAndSaveClip(SDL_Surface *surface, int centerHeight, int centerWidth
	, std::string spriteSheetFileName, std::string clipFileName);
	SDL_Surface * createDestination();
	void lock(SDL_Surface *surface);
	void unlock(SDL_Surface *surface);
	~Grid();
};

//clips a sprite sheet on a global clip variable
void toClip(SDL_Surface * surface);

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

//convert int to string
std::string intToString(int n);

#endif // LAZYFUNCTIONSANDCONSTANTS_H_INCLUDED