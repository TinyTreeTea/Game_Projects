#ifndef ZOMBIE_KILLER_H_INCLUDED
#define ZOMBIE_KILLER_H_INCLUDED

#include <SDL.h>
#include "LazyFooFunctionsAndConstants.h"
#include <fstream>

//all information unique to a single rotation clip.
struct Information
{
	SDL_Rect clip;			//the clip for the zombieKiller
	SDL_Rect clip2;			//the clip for the spark
	SDL_Rect clip3;			//the clip for the bullet
	SDL_Rect clip4;			//the clip for the zombie
	SDL_Rect clip5;			//the clip for the blood
	SDL_Rect clip6;			//the clip for the dead zombie
	int xTipOfGun;
	int yTipOfGun;
	double angle;  //starts at 12 oclock, and heads counter clock wise.
};

struct SpawnData
{
	int time;
	//int x,y;		//location
	//int type;		//type of monster to spawn
	SpawnData * next;
	SpawnData(int t,SpawnData * n):time(t),next(n){}
};


struct Bullet
{
	double angle;
	double x,y;
	SDL_Rect area;
	int static speed;
	Bullet * next;
	Bullet(double a,double X, double Y, SDL_Rect * c, Bullet * n):angle(a),x(X),y(Y),next(n){
		if(c)
			area = *c;
		else
			area.h = area.w = area.x = area.y = 0;
	}
};

struct Zombie
{
	int static speed; //pixels per second
	unsigned int hitRate;
	int life;
	Zombie *next;
	double x, y; //coordinates of the center of the zombie;
	double deltaX, deltaY; //the change per frame on the angle;
	Information * info;	//the sprite sheet clipping information.
	int infoNum; //the official rotation required, (the index of info).
	SDL_Rect collisionBox;
	double angle;
	int restart;
	int isHit;
	Zombie(Zombie * head2);
	void update();
	void move();
	bool checkCollision(Bullet * bullet);
};



class ZombieKiller
{	
public:
	int life;//zombieKillers life
	SDL_Rect camera;//the camera
	SDL_Rect collisionBox;//the area of zombieKiller
	int xvel, yvel;//speed of character
	int XCurser, YCurser;//x and y of the mouse
	Information * info;
	int isShooting; //true if shooting, false if not shooting.
	double clipingAngel;//its angel with the x line,starting at 12:00 against clockwise
	int state;//t what animation the zombieKiller is at
	bool stateDirection;//true is +, false is -
	int canApplyAnimation;//for every 6 frames a new animation apears,if(canApplyAnimation == 0) then apply animation
	int fireRate;

	//the head of the list of bullets.
	Bullet * head;

	//the head and count of the list of zombies
	int zombieCount, deadZombieCount;
	Zombie * head2;
	bool zombieSpawn; //true if zombie should spawn

	//the list to the spawning sequence
	SpawnData * head3;
	int frame;		//the frame and second that the game is on
	int second;

    //Initializes the variables
    ZombieKiller();

	//Destroy all memory created on the heap
	~ZombieKiller();
    
    //Takes key presses and adjusts the killer's velocity
    void handle_input();
    
    //Moves the killer
    void move();

	//gets the mouses state and changes XCurser and YCurser and modifies cliping angel
	void handleMouse();
    
    //Shows the killer on the screen
    void show();

	//changes the animation variables if needed
	void changeAnimation();
    
    //Sets the camera over the killer
    void set_camera();

	void bullet_managment();

	void zombie_managment();

	//handles collision between zombie killer and the zombies
	void collision_manegment();

	//checks if zombie killer finished the game
	void is_finished();
};

#endif //ZOMBIE_KILLER_H_INCLUDED