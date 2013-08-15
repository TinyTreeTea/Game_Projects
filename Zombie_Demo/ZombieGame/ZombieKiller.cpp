#include "ZombieKiller.h"
#include "LazyFooFunctionsAndConstants.h"
#include "Globals.h"
#include <math.h>
#include <iostream>

int Bullet::speed = 400;
int Zombie::speed = 50;

Zombie::Zombie(Zombie *head2):next(head2)
{
	life = 10;
	x = rand() % LEVEL_WIDTH;
	y = rand() % LEVEL_HEIGHT;
	int wall = rand() % 4;
	if(wall == 0)
		x = -50;
	else if(wall == 1)
		x = LEVEL_WIDTH + 50;
	else if(wall == 2)
		y = -50;
	else
		y = LEVEL_HEIGHT + 50;
	deltaX = deltaY = 0;
	info = zombieInformation;
	infoNum = 0;
	angle = 0;
	collisionBox.x = (int)(x - info->clip4.w / 2);
	collisionBox.y = (int)(y - info->clip4.h / 2);
	collisionBox.w = info->clip4.w;
	collisionBox.h = info->clip4.h;
	restart = 0;
	isHit = 0;
	hitRate = 0;
}

void Zombie::update()
{
	infoNum = (int)((angle+0.0)/(6.2831853/MODERATION) + 0.5);
	if(infoNum == MODERATION)
		infoNum = 0;
	infoNum = (infoNum+32)%MODERATION;

	double distance = ((speed+0.0)/FRAMES_PER_SECOND);

	deltaX = (sin(angle)*distance);
	deltaY = (cos(angle)*distance);
}

void Zombie::move()
{
	x += deltaX;
	y += deltaY;
	collisionBox.x = (int)(x - collisionBox.w / 2);
	collisionBox.y = (int)(y - collisionBox.h / 2);
}

bool Zombie::checkCollision(Bullet * bullet)
{
	return ( collisionBox.x < bullet->x && collisionBox.x + collisionBox.w > bullet->x && 
			 collisionBox.y < bullet->y && collisionBox.y + collisionBox.h > bullet->y );
}

ZombieKiller::ZombieKiller()
{
	collisionBox.x = LEVEL_WIDTH / 2;
	collisionBox.y = LEVEL_HEIGHT / 2;
	collisionBox.w = zombieKillerClip->w;
	collisionBox.h = zombieKillerClip->h;
	xvel = yvel = 0;
	//Center the camera over the killer
    camera.x = ( collisionBox.x + collisionBox.w / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( collisionBox.y + collisionBox.h / 2 ) - SCREEN_HEIGHT / 2;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
	clipingAngel = 0;
	state = 0;
	stateDirection = true;
	isShooting = 0;
	info = zombieInformation;
	canApplyAnimation = 0;
	fireRate = 1;
	head = NULL;
	head2 = NULL;
	zombieSpawn = false;
	zombieCount = 0;
	head3 = spawndata;
	frame = second = 0;
	deadZombieCount = 0;
	life = 100;
}



ZombieKiller::~ZombieKiller()
{
	Bullet *runner = head, *destroy = head;
	while(runner != NULL)
	{
		runner = runner->next;
		delete destroy;
		destroy = runner;
	}

	Zombie *runner2 = head2, *destroy2 = head2;
	while(runner2 != NULL)
	{
		runner2 = runner2->next;
		delete destroy2;
		destroy2 = runner2;
	}
}

void ZombieKiller::handle_input()
{
	//If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
			case SDLK_w: yvel -= 2; break;
			case SDLK_s: yvel += 2; break;
			case SDLK_a: xvel -= 2; break;
			case SDLK_d: xvel += 2; break;    
        }
    }
	//If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
			case SDLK_w: yvel += 2; break;
			case SDLK_s: yvel -= 2; break;
			case SDLK_a: xvel += 2; break;
			case SDLK_d: xvel -= 2; break;   
        }        
    }

	else if( event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
			isShooting = fireRate;
		else if(event.button.button == SDL_BUTTON_RIGHT)
			zombieSpawn = true;
	}

	else if( event.type == SDL_MOUSEBUTTONUP )
	{
		if(event.button.button == SDL_BUTTON_LEFT)
			isShooting = 0;
	}
}

void ZombieKiller::move()
{
	//Move the killer left or right
    collisionBox.x += xvel;
    
    //If the killer went too far to the left or right
    if(collisionBox.x < 0)
    {
        //move back
        collisionBox.x = 0;  
    }

	else if (collisionBox.x + collisionBox.w > LEVEL_WIDTH)
	{
		//move back
        collisionBox.x = LEVEL_WIDTH - collisionBox.w;  
	}
    
    //Move the killer up or down
    collisionBox.y += yvel;
    
    //If the killer went too far up or down
    if(collisionBox.y < 0)
    {
        //move back
        collisionBox.y = 0;    
    } 

	else if(collisionBox.y + collisionBox.h > LEVEL_HEIGHT)
	{
		collisionBox.y = LEVEL_HEIGHT - collisionBox.h;
	}
}

void ZombieKiller::changeAnimation()
{
	if(xvel !=0 || yvel != 0 || canApplyAnimation == 0)
		++canApplyAnimation;
	canApplyAnimation %= 6;

	if(canApplyAnimation == 0)
	{
		if(stateDirection)
		{
			if(state != 5)
			{
				++state;
			}
			else
			{
				stateDirection = false;
			}
		}
		else
		{
			if(state != -5)
			{
				--state;
			}
			else
			{
				stateDirection = true;
			}
		}
	}
}

void ZombieKiller::set_camera()
{
    //Center the camera over the killer
    camera.x = ( collisionBox.x + collisionBox.w / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( collisionBox.y + collisionBox.h / 2 ) - SCREEN_HEIGHT / 2;
    
    //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;    
    }
    if( camera.y < 0 )
    {
        camera.y = 0;    
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;    
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;    
    }    
}

void ZombieKiller::show()
{

	apply_surface(0,0,background,screen, &camera);
	switch(state)
	{
	case 0:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheet,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case 1:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheet1,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case 2:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheet2,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case 3:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheet3,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case 4:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheet4,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case 5:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheet5,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case -1:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheetMinus1,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case -2:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheetMinus2,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case -3:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheetMinus3,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case -4:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheetMinus4,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	case -5:
		apply_surface(collisionBox.x - camera.x,collisionBox.y - camera.y,zombieKillerSurfaceSpriteSheetMinus5,screen,
			&zombieKillerClip[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64]);
		break;
	}



	Zombie * runner2 = head2;
	while(runner2)
	{
		apply_surface(runner2->collisionBox.x - camera.x, runner2->collisionBox.y - camera.y,zombieSpriteSheet,screen,&(info[runner2->infoNum].clip4));
		runner2 = runner2->next;
	}

	Bullet * runner = head;
	int finalX,finalY;
	while(runner)
	{
		finalX = runner->x - camera.x - info->clip3.w/2;
		finalY = runner->y - camera.y - info->clip3.h/2;
		apply_surface(finalX,finalY,bulletSpriteSheet,screen,&(runner->area));
		runner = runner->next;
	}



	if(isShooting > fireRate/3){
		apply_surface(collisionBox.x - camera.x + info[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64].xTipOfGun - info->clip2.w/2 , collisionBox.y - camera.y + info[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64].yTipOfGun - info->clip2.h/2, sparksSpriteSheet,screen,&(info[(int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64].clip2));

	}

}

void ZombieKiller::handleMouse()
{
	SDL_GetMouseState(&XCurser,&YCurser);
	if(XCurser == (collisionBox.x + collisionBox.w / 2 - camera.x))
	{
		if(YCurser < (collisionBox.y + collisionBox.h / 2 - camera.y))
		{
			clipingAngel = 0;
			return;
		}
		else
			clipingAngel = 180;
	}
	if((collisionBox.x + collisionBox.w / 2 - camera.x) > XCurser && 
		(collisionBox.y + collisionBox.h / 2 - camera.y) > YCurser)
	{
		clipingAngel = 90 - (std::atan((double)(YCurser - (collisionBox.y + collisionBox.h / 2 - camera.y)) / 
		(XCurser - (collisionBox.x + collisionBox.w / 2 - camera.x))) * 180 / 3.14159265);
		return;
	}
	if((collisionBox.x + collisionBox.w / 2 - camera.x) > XCurser && 
		(collisionBox.y + collisionBox.h / 2 - camera.y) < YCurser)
	{
		clipingAngel = std::atan((double)(YCurser - (collisionBox.y + collisionBox.h / 2 - camera.y)) / 
		(XCurser - (collisionBox.x + collisionBox.w / 2 - camera.x))) * 180 / 3.14159265;
		clipingAngel += 180;
		clipingAngel = 270 - clipingAngel;
		return;
	}
	if((collisionBox.x + collisionBox.w / 2 - camera.x) < XCurser && 
		(collisionBox.y + collisionBox.h / 2 - camera.y) < YCurser)
	{
		clipingAngel = 180 + (90 - (std::atan((double)(YCurser - (collisionBox.y + collisionBox.h / 2 - camera.y)) / 
		(XCurser - (collisionBox.x + collisionBox.w / 2 - camera.x))) * 180 / 3.14159265));
		return;
	}
	if((collisionBox.x + collisionBox.w / 2 - camera.x) < XCurser && 
		(collisionBox.y + collisionBox.h / 2 - camera.y) > YCurser)
	{
		clipingAngel = std::atan((double)(YCurser - (collisionBox.y + collisionBox.h / 2 - camera.y)) / 
		(XCurser - (collisionBox.x + collisionBox.w / 2 - camera.x))) * 180 / 3.14159265;
		clipingAngel += 180;
		clipingAngel = 270 - clipingAngel;
		clipingAngel += 180;
		return;
	}
}

void ZombieKiller::bullet_managment()
{
	Bullet ** runner = &head;
	Bullet * doomed = NULL;
	int direction = (int)(clipingAngel / (360.0 / zombieKillerClipLength) + 0.5) % 64;
	if(direction < 0 || direction > 70){
		std::cout << "direction mistake \n";
		exit(1);
	}
	if(isShooting == fireRate)
	{
		Bullet * newBullet = new Bullet(clipingAngel,collisionBox.x + info[direction].xTipOfGun,collisionBox.y + info[direction].yTipOfGun, &(info[direction].clip3),head);
		head = newBullet;
	}


	if(isShooting > 1)
		--isShooting;
	else if(isShooting == 1)
		isShooting = 20;


	double distance = ((*runner)->speed+0.0)/FRAMES_PER_SECOND;			//distance per frame
	double radianAngle;
	while(*runner)
	{
		radianAngle = (((*runner)->angle+0.0)/360)*6.281853;
		(*runner)->x -= sin(radianAngle)*distance;
		(*runner)->y -= cos(radianAngle)*distance;
		if((*runner)->x < 0 || (*runner)->x > LEVEL_WIDTH || (*runner)->y < 0 || (*runner)->y > LEVEL_HEIGHT)
		{
			doomed = *runner;
			*runner = (*runner)->next;
			delete doomed;
			continue;
		}

		runner = &((*runner)->next);
	}

}

void ZombieKiller::zombie_managment()
{
	if(head3)
	{
		++frame;
		if(frame == FRAMES_PER_SECOND)
		{
			frame = 0;
			++second;
		}

		while(head3 && head3->time <= second)
		{
			//SpawnData * doomed = head3;
			head2 = new Zombie(head2);
			++zombieCount;
			head3 = head3->next;
			//delete doomed;

		}
	}

	if(zombieSpawn)
	{
		head2 = new Zombie(head2);
		++zombieCount;
		zombieSpawn = false;
	}

	Zombie ** runner = &head2;
	int randomChasingDestination = rand() % 4;
	int chasingX, chasingY;
	while(*runner)
	{
		if((*runner)->restart == 0)
		{
			if(randomChasingDestination == 0)
			{
				chasingX = collisionBox.x + collisionBox.w/2;
				chasingY = collisionBox.y + collisionBox.h/2;
			}
			else if(randomChasingDestination == 1)
			{
				chasingX = collisionBox.x + collisionBox.w/2 + xvel*FRAMES_PER_SECOND;
				chasingY = collisionBox.y + collisionBox.h/2 + yvel*FRAMES_PER_SECOND;
			}
			else if(randomChasingDestination == 2)
			{
				chasingX = collisionBox.x + collisionBox.w/2 + xvel*FRAMES_PER_SECOND*2;
				chasingY = collisionBox.y + collisionBox.h/2 + yvel*FRAMES_PER_SECOND*2;
			}
			else if(randomChasingDestination == 3)
			{
				chasingX = collisionBox.x + collisionBox.w/2 + xvel*FRAMES_PER_SECOND*3;
				chasingY = collisionBox.y + collisionBox.h/2 + yvel*FRAMES_PER_SECOND*3;
			}
			else
			{
				chasingX = collisionBox.x + collisionBox.w/2;
				chasingY = collisionBox.y + collisionBox.h/2;
			}
			(*runner)->angle = calculateRadianAngle((*runner)->x,(*runner)->y,chasingX,chasingY);
			(*runner)->update();
			(*runner)->restart = rand()%(FRAMES_PER_SECOND*5) + 10;
			randomChasingDestination = rand() % 4;
		}

		if((*runner)->isHit == 0)
		{
			if(!((*runner)->x <= collisionBox.x + collisionBox.w && (*runner)->y <= collisionBox.y + collisionBox.h 
				&& (*runner)->x >= collisionBox.x && (*runner)->y >= collisionBox.y))
				(*runner)->move();
		}
		else
			--(*runner)->isHit;
		--(*runner)->restart;

		Bullet **bulletRunner = &head;
		bool tester = true;
		while(*bulletRunner != NULL)
		{
			tester = true;

			if((*runner)->checkCollision(*bulletRunner) == true)
			{
				apply_surface((*runner)->x - info->clip5.w/2,(*runner)->y - info->clip5.h/2,bloodSpriteSheet,background,&info[(*runner)->infoNum].clip5);

					//delete bullet
				Bullet * doomedBullet = *bulletRunner;
				*bulletRunner = (*bulletRunner)->next;
				delete doomedBullet;
				tester = false;
				(*runner)->life -= 10;
					//zombie is hit
				if(--(*runner)->life <= 0)
				{
				    //kill zombie
					apply_surface((*runner)->x - info->clip6.w/2,(*runner)->y - info->clip6.h/2,deadSpriteSheet,background,&info[(*runner)->infoNum].clip6);
					++deadZombieCount;
					--zombieCount;

					Zombie * doomedZombie = *runner;
					*runner = (*runner)->next;


					delete doomedZombie;

					goto endOfOuterLoop;
				}
				(*runner)->isHit += rand() % FRAMES_PER_SECOND + 10;
				
			}
			if(tester)
				bulletRunner = &((*bulletRunner)->next);
		}


		runner = &((*runner)->next);
		
endOfOuterLoop:;
	}

}

//handles collision between zombie killer and the zombies
void ZombieKiller::collision_manegment()
{
	Zombie *runner = head2;
	while(runner != NULL)
	{
		++runner->hitRate;
		if (runner->x <= collisionBox.x + collisionBox.w && runner->y <= collisionBox.y + collisionBox.h 
			&& runner->x >= collisionBox.x && runner->y >= collisionBox.y)
		{
			if(runner->hitRate >= 50)
			{
				--life;
				if(life == 0)
				{
					//Quit the program
					set_next_state(STATE_GAME_OVER);

					zombieKilled = deadZombieCount;
				}
				runner->hitRate = 0;
			}
		}
		runner = runner->next;
	}
}
//checks if zombie killer finished the game
void ZombieKiller::is_finished()
{
	if(head3 == NULL && head2 == NULL)
	{
		zombieKilled = deadZombieCount;
		set_next_state(STATE_GAME_OVER);
	}
}