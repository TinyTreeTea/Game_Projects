#include "Board.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

extern void apply_surface(int x,int y,SDL_Surface *source,SDL_Surface *destination,SDL_Rect *clip = NULL);
extern SDL_Surface *gameOver;
extern SDL_Surface *screen;
extern SDL_Surface *gameOverMessage;
extern SDL_Color gameOverFontTextColor;
extern TTF_Font *gameOverFont;
Board::Board()
{
    score = 0;
    srand(time(NULL));
    shape = rand() % 7;
    state = 0;
    for(int i=0; i<10; ++i)
        latitude[i] = -1;
    if(shape == 0 || shape == 3 || shape == 4)
        x = 3;
    else
        x = 4;
    y = 0;

    switch(shape)
    {
        case 0: latitude[3] = latitude[4] = latitude[5] = 2;
			break;
        case 1: latitude[4] = latitude[5] = 2;
			break;
        case 2: latitude[4] = 4;
			break;
        case 3: latitude[3] = 1; latitude[4] = latitude[5] = 2;
			break;
        case 4: latitude[3] = latitude[4] = 2; latitude[5] = 1;
			break;
        case 5: case 6: latitude[4] = latitude[5] = 3;
			break;
        default:;
    }
    for(int i = 0;i < 18;++i)
        for(int j = 0;j < 10;++j)
			slots[i][j].isOccupied = false;
}

void Board::eraseLine(int erasingPoint)
{
    bool end = false;
    for(int i = 0;i < 10;++i)
    {
		slots[erasingPoint][i].isOccupied = false;
    }

    for(int i=erasingPoint-1; i>=0; --i)
    {
        end = false;
        for(int j=0; j<10; ++j)
        {
            slots[i+1][j] = slots[i][j];
            if(slots[i][j])
                end = true;
        }
        if(!end)
            break;
    }
    ++score;


}

void Board::checkLine()
{
	//old and efficent erase line code but it is buggy for
	//some reason
    /*int checkFromWhere = -1,stopAtWhere = 19;
    for(int i=0;i < 10;++i)
    {
        if(latitude[i] > checkFromWhere)
            checkFromWhere = latitude[i] - 1;
        if(latitude[i] < stopAtWhere && latitude[i] != -1)
            stopAtWhere = latitude[i] - 1;
    }
    while(checkFromWhere != stopAtWhere + 1)
    {
        for(int i = 0;i < 10;++i)
        {
            if(!slots[checkFromWhere][i])
            {
                goto continueWhileLoop;
            }
        }
        eraseLine(checkFromWhere);
        --stopAtWhere;
        continue;
        continueWhileLoop:
        ++checkFromWhere;
    }*/
	bool eraseLine2;
	for(int i=17;i >=0;--i)
	{
		eraseLine2 = true;
		for(int j=0;j<10;++j)
		{
			if(!slots[i][j])
				eraseLine2 = false;
		}
		if(eraseLine2)
		{
			eraseLine(i);
			++i;
		}
	}
}

bool Board::checkCollision1()
{
    for(int i = 0;i < 10;++i)
        if(latitude[i] == 18 || (latitude[i] != -1 && slots[latitude[i]][i]))
            return true;
    return false;
}

bool Board::goDown()
{
    if(checkCollision1())
    {
        switch(shape)
        {
            case 0:
                switch(state)
                {
                    case 0:
						slots[y][x+1].isOccupied = slots[y+1][x].isOccupied =
							slots[y+1][x+1].isOccupied = slots[y+1][x+2].isOccupied = true;
						slots[y][x+1].color = slots[y+1][x].color =
							slots[y+1][x+1].color = slots[y+1][x+2].color = 0;
                        break;
                    case 1:
						slots[y][x+1].isOccupied = slots[y+1][x+1].isOccupied =
							slots[y+2][x+1].isOccupied = slots[y+1][x+2].isOccupied = true;
						slots[y][x+1].color = slots[y+1][x+1].color =
							slots[y+2][x+1].color = slots[y+1][x+2].color = 0;
                        break;
                    case 2:
						slots[y+1][x].isOccupied = slots[y+1][x+1].isOccupied =
							slots[y+1][x+2].isOccupied = slots[y+2][x+1].isOccupied = true;
						slots[y+1][x].color = slots[y+1][x+1].color =
							slots[y+1][x+2].color = slots[y+2][x+1].color = 0;
                        break;
                    default:
						slots[y+1][x].isOccupied = slots[y][x+1].isOccupied =
							slots[y+1][x+1].isOccupied = slots[y+2][x+1].isOccupied = true;
						slots[y+1][x].color = slots[y][x+1].color =
							slots[y+1][x+1].color = slots[y+2][x+1].color = 0;
                }
                break;
            case 1:
				slots[y][x].isOccupied = slots[y+1][x].isOccupied =
					slots[y][x+1].isOccupied = slots[y+1][x+1].isOccupied = true;
				slots[y][x].color = slots[y+1][x].color =
					slots[y][x+1].color = slots[y+1][x+1].color = 1;
                break;
            case 2:
                switch(state)
                {
				case 0:case 2:
					slots[y][x].isOccupied = slots[y+1][x].isOccupied =
							slots[y+2][x].isOccupied = slots[y+3][x].isOccupied = true;
					slots[y][x].color = slots[y+1][x].color =
						slots[y+2][x].color = slots[y+3][x].color = 2;
                        break;
                    default:
						slots[y][x+1].isOccupied = slots[y][x].isOccupied =
							slots[y][x+2].isOccupied = slots[y][x+3].isOccupied = true;
						slots[y][x+1].color = slots[y][x].color =
							slots[y][x+2].color = slots[y][x+3].color = 2;
                }
                break;
            case 3:
                switch(state)
                {
				case 0: case 2:
					slots[y][x].isOccupied = slots[y][x+1].isOccupied =
						slots[y+1][x+1].isOccupied = slots[y+1][x+2].isOccupied = true;
					slots[y][x].color = slots[y][x+1].color =
						slots[y+1][x+1].color = slots[y+1][x+2].color = 3;
                        break;
                    default:
						slots[y][x+1].isOccupied = slots[y+1][x].isOccupied =
							slots[y+1][x+1].isOccupied = slots[y+2][x].isOccupied = true;
						slots[y][x+1].color = slots[y+1][x].color =
							slots[y+1][x+1].color = slots[y+2][x].color = 3;
                }
                break;
            case 4:
                switch(state)
                {
				case 0: case 2:
					slots[y][x+1].isOccupied = slots[y][x+2].isOccupied =
						slots[y+1][x].isOccupied = slots[y+1][x+1].isOccupied = true;
					slots[y][x+1].color = slots[y][x+2].color =
						slots[y+1][x].color = slots[y+1][x+1].color = 4;
                        break;
                    default:
						slots[y][x].isOccupied = slots[y+1][x].isOccupied =
							slots[y+1][x+1].isOccupied = slots[y+2][x+1].isOccupied = true;
						slots[y][x].color = slots[y+1][x].color =
							slots[y+1][x+1].color = slots[y+2][x+1].color = 4;
                }
                break;
            case 5:
                switch(state)
                {
                    case 0:
						slots[y][x].isOccupied = slots[y+1][x].isOccupied =
							slots[y+2][x].isOccupied = slots[y+2][x+1].isOccupied = true;
						slots[y][x].color = slots[y+1][x].color =
							slots[y+2][x].color = slots[y+2][x+1].color = 5;
                        break;
                    case 1:
						slots[y][x].isOccupied = slots[y][x+1].isOccupied =
							slots[y][x+2].isOccupied = slots[y+1][x].isOccupied = true;
						slots[y][x].color = slots[y][x+1].color =
							slots[y][x+2].color = slots[y+1][x].color = 5;
                        break;
                    case 2:
						slots[y][x].isOccupied = slots[y][x+1].isOccupied =
							slots[y+1][x+1].isOccupied = slots[y+2][x+1].isOccupied = true;
						slots[y][x].color = slots[y][x+1].color =
							slots[y+1][x+1].color = slots[y+2][x+1].color = 5;
                        break;
                    default:
						slots[y][x+2].isOccupied = slots[y+1][x].isOccupied =
							slots[y+1][x+1].isOccupied = slots[y+1][x+2].isOccupied = true;
						slots[y][x+2].color = slots[y+1][x].color =
							slots[y+1][x+1].color = slots[y+1][x+2].color = 5;
                }
                break;
            case 6:
                switch(state)
                {
                    case 0:
						slots[y][x+1].isOccupied = slots[y+1][x+1].isOccupied =
							slots[y+2][x].isOccupied = slots[y+2][x+1].isOccupied = true;
						slots[y][x+1].color = slots[y+1][x+1].color =
							slots[y+2][x].color = slots[y+2][x+1].color = 6;
                        break;
                    case 1:
						slots[y][x].isOccupied = slots[y+1][x].isOccupied =
							slots[y+1][x+1].isOccupied = slots[y+1][x+2].isOccupied = true;
						slots[y][x].color = slots[y+1][x].color =
							slots[y+1][x+1].color = slots[y+1][x+2].color = 6;
                        break;
                    case 2:
						slots[y][x].isOccupied = slots[y][x+1].isOccupied =
							slots[y+1][x].isOccupied = slots[y+2][x].isOccupied = true;
						slots[y][x].color = slots[y][x+1].color =
							slots[y+1][x].color = slots[y+2][x].color = 6;
                        break;
                    default:
						slots[y][x].isOccupied = slots[y][x+1].isOccupied =
							slots[y][x+2].isOccupied = slots[y+1][x+2].isOccupied = true;
						slots[y][x].color = slots[y][x+1].color =
							slots[y][x+2].color = slots[y+1][x+2].color = 6;
                }
                break;
            default:;
        }

        checkLine();
        //srand(time(NULL));
        shape = rand() % 7;
        state = 0;
        for(int i=0; i<10; ++i)
            latitude[i] = -1;

        if(shape == 0 || shape == 3 || shape == 4)
            x = 3;
        else
            x = 4;
		y=0;
        switch(shape)
        {
            case 0: latitude[3] = latitude[4] = latitude[5] = 2;
			if(checkCollision1() || checkCollision2())
			{
				apply_surface(0,0,gameOver,screen);
				//Render the text
				char buffer[4];
				buffer[3] = '/n';
				gameOverMessage = TTF_RenderText_Solid( gameOverFont, itoa(score,buffer,10), gameOverFontTextColor );

				//If there was an error in rendering the text
				if( gameOverMessage == NULL )
				{
					std::cerr << SDL_GetError() << std::endl;
					exit(1);
			    }
				apply_surface(140,272,gameOverMessage,screen);
				SDL_Flip(screen);
				SDL_Delay(10000);
				exit(0);
			}
				break;
        case 1: latitude[4] = latitude[5] = 2;
			if(checkCollision1() || checkCollision2())
			{
				apply_surface(0,0,gameOver,screen);
				//Render the text
				char buffer[4];
				buffer[3] = '/n';
				gameOverMessage = TTF_RenderText_Solid( gameOverFont, itoa(score,buffer,10), gameOverFontTextColor );

				//If there was an error in rendering the text
				if( gameOverMessage == NULL )
				{
					std::cerr << SDL_GetError() << std::endl;
					exit(1);
			    }
				apply_surface(140,272,gameOverMessage,screen);
				SDL_Flip(screen);
				SDL_Delay(10000);
				exit(0);
			}
			break;
        case 2: latitude[4] = 4;
			if(checkCollision1() || checkCollision2())
			{
				apply_surface(0,0,gameOver,screen);
				//Render the text
				char buffer[4];
				buffer[3] = '/n';
				gameOverMessage = TTF_RenderText_Solid( gameOverFont, itoa(score,buffer,10), gameOverFontTextColor );

				//If there was an error in rendering the text
				if( gameOverMessage == NULL )
				{
					std::cerr << SDL_GetError() << std::endl;
					exit(1);
			    }
				apply_surface(140,272,gameOverMessage,screen);
				SDL_Flip(screen);
				SDL_Delay(10000);
				exit(0);
			}
			break;
        case 3: latitude[3] = 1; latitude[4] = latitude[5] = 2;
			if(checkCollision1() || checkCollision2())
			{
				apply_surface(0,0,gameOver,screen);
				//Render the text
				char buffer[4];
				buffer[3] = '/n';
				gameOverMessage = TTF_RenderText_Solid( gameOverFont, itoa(score,buffer,10), gameOverFontTextColor );

				//If there was an error in rendering the text
				if( gameOverMessage == NULL )
				{
					std::cerr << SDL_GetError() << std::endl;
					exit(1);
			    }
				apply_surface(140,272,gameOverMessage,screen);
				SDL_Flip(screen);
				SDL_Delay(10000);
				exit(0);
			}
			break;
        case 4: latitude[3] = latitude[4] = 2; latitude[5] = 1;
			if(checkCollision1() || checkCollision2())
			{
				apply_surface(0,0,gameOver,screen);
				//Render the text
				char buffer[4];
				buffer[3] = '/n';
				gameOverMessage = TTF_RenderText_Solid( gameOverFont, itoa(score,buffer,10), gameOverFontTextColor );

				//If there was an error in rendering the text
				if( gameOverMessage == NULL )
				{
					std::cerr << SDL_GetError() << std::endl;
					exit(1);
			    }
				apply_surface(140,272,gameOverMessage,screen);
				SDL_Flip(screen);
				SDL_Delay(10000);
				exit(0);
			}
			break;
        case 5: case 6: latitude[4] = latitude[5] = 3;
			if(checkCollision1() || checkCollision2())
			{
				apply_surface(0,0,gameOver,screen);
				//Render the text
				char buffer[4];
				buffer[3] = '/n';
				gameOverMessage = TTF_RenderText_Solid( gameOverFont, itoa(score,buffer,10), gameOverFontTextColor );

				//If there was an error in rendering the text
				if( gameOverMessage == NULL )
				{
					std::cerr << SDL_GetError() << std::endl;
					exit(1);
			    }
				apply_surface(140,272,gameOverMessage,screen);
				SDL_Flip(screen);
				SDL_Delay(10000);
				exit(0);
			}
			break;
        default:;
        }


        return false;
    }
    for(int i = 0;i < 10;++i)
        if(latitude[i] != -1)
            ++latitude[i];
    ++y;
	return true;
}

bool Board::checkCollision2()
{
    switch(shape)
    {
        case 0:
            switch(state)
            {
                case 0:
                    if(slots[y+2][x+1] || y>15)
                        return true;
                    break;
                case 1:
                    if(x<0 || slots[y+1][x])
                        return true;
                    break;
                case 2:
                    if(slots[y][x+1])
                        return true;
                    break;
                default:
                    if(x>7 || slots[y+1][x+2])
                        return true;
                    break;
            }
            break;
        case 2:
            switch(state)
            {
			case 0:case 2:
                    if(x>6 || slots[y][x+1] || slots[y][x+2] || slots[y][x+3])
                        return true;
                    break;
                default:
                    if(slots[y+1][x] || slots[y+2][x] || slots[y+3][x] || y>14)
                        return true;
                    break;
            }
            break;
        case 3:
            switch(state)
            {
			case 0:case 2:
                    if(slots[y+1][x] || slots[y+2][x] || y>15)
                        return true;
                    break;
                default:
                    if(x>7 || slots[y][x] || slots[y+1][x+2])
                        return true;
                    break;
            }
            break;
        case 4:
            switch(state)
            {
			case 0: case 2:
                    if(slots[y][x] || slots[y+2][x+1] || y>15)
                        return true;
                    break;
                default:
                    if(x>7 || slots[y][x+1] || slots[y][x+2])
                        return true;
                    break;
            }
            break;
        case 5:
            switch(state)
            {
                case 0:
                    if(x>7 || slots[y][x+1] || slots[y][x+2])
                        return true;
                    break;
                case 1:
                    if(slots[y+1][x+1] || slots[y+1][x+2] || y>15)
                        return true;
                    break;
                case 2:
                    if(x>7 || slots[y+1][x] || slots[y+2][x] || slots[y][x+2])
                        return true;
                    break;
                default:
                    if(slots[y][x] || slots[y+2][x] || slots[y+2][x+1] || y>15)
                        return true;
                    break;
            }
            break;
        default:
            switch(state)
            {
                case 0:
                    if(x>7 || slots[y][x] || slots[y+1][x] || slots[y+1][x+2])
                        return true;
                    break;
                case 1:
                    if(slots[y+2][x] || slots[y][x+1] || y>15)
                        return true;
                    break;
                case 2:
                    if(x>7 || slots[y][x+2] || slots[y+1][x+2])
                        return true;
                    break;
                default:
                    if(slots[y+2][x] || slots[y+2][x+1] || slots[y+1][x+1] || y>15)
                        return true;
                    break;
            }
    }
    return false;
}

bool Board::rotate()
{
    if(checkCollision2())
        return false;
    if(state == 3)
        state = 0;
    else
        ++state;

    switch(shape)
    {
        case 0:
            switch(state)
            {
                case 0:
                    --latitude[x+1];
                    latitude[x+2] = y+2;
                    break;
                case 1:
                    latitude[x] = -1;
                    ++latitude[x+1];
                    break;
                case 2:
                    latitude[x] = y+2;
                    break;
                case 3:
                    latitude[x+2] = -1;
                    break;
            }
            break;
        case 2:
            switch(state)
            {
			case 0: case 2:
                    latitude[x] = y+4;
                    latitude[x+1] = -1;
                    latitude[x+2] = -1;
                    latitude[x+3] = -1;
                    break;
                default:
                    latitude[x] = y+1;
                    latitude[x+1] = y+1;
                    latitude[x+2] = y+1;
                    latitude[x+3] = y+1;
                    break;
            }
            break;
        case 3:
            switch(state)
            {
			case 0: case 2:
                    latitude[x] = y+1;
                    latitude[x+1] = y+2;
                    latitude[x+2] = y+2;
                    break;
                default:
                    latitude[x] = y+3;
                    latitude[x+1] = y+2;
                    latitude[x+2] = -1;
                    break;
            }
            break;
        case 4:
            switch(state)
            {
			case 0: case 2:
                    --latitude[x+1];
                    latitude[x+2] = y+1;
                    break;
                default:
                    ++latitude[x+1];
                    latitude[x+2] = -1;
                    break;
            }
            break;
        case 5:
            switch(state)
            {
                case 0:
                    ++latitude[x];
                    ++latitude[x+1];
                    latitude[x+2] = -1;
                    break;
                case 1:
                    --latitude[x];
                    latitude[x+1] -= 2;
                    latitude[x+2] = y+1;
                    break;
                case 2:
                    --latitude[x];
                    latitude[x+1] += 2;
                    latitude[x+2] = -1;
                    break;
                case 3:
                    ++latitude[x];
                    --latitude[x+1];
                    latitude[x+2] = y+2;
                    break;
            }
            break;
        case 6:
            switch(state)
            {
                case 0:
                    latitude[x]+=2;
                    latitude[x+1]+=2;
                    latitude[x+2] = -1;
                    break;
                case 1:
                    --latitude[x];
                    --latitude[x+1];
                    latitude[x+2] = y+2;
                    break;
                case 2:
                    ++latitude[x];
                    --latitude[x+1];
                    latitude[x+2] = -1;
                    break;
                case 3:
                    latitude[x] -= 2;
                    latitude[x+2] = y+2;
                    break;
            }
            break;
		default:;
    }
    return true;
}
bool Board::checkCollisionWithRightWall()
{
    switch(shape)
    {
        case 0:
            switch(state)
            {
                case 0:
                    if(x>6 || slots[y][x+2] || slots[y+1][x+3])
                        return true;
                    break;
                case 1:
                    if(x>6 || slots[y][x+2] || slots[y+1][x+3] || slots[y+2][x+2])
                        return true;
                    break;
                case 2:
                    if(x>6 || slots[y+1][x+3] || slots[y+2][x+2])
                        return true;
                    break;
                default:
                    if(x>7 || slots[y][x+2] || slots[y+1][x+2] || slots[y+2][x+2])
                        return true;
                    break;
            }
            break;
        case 1:
        {
            if(x>7 || slots[y][x+2] || slots[y+1][x+2])
                return true;
            break;
        }
        case 2:
        {
            switch(state)
            {
			case 0:case 2:
                    if(x>8 || slots[y][x+1] || slots[y+1][x+1] || slots[y+2][x+1] || slots[y+3][x+1])
                        return true;
                    break;
                default:
                    if(x>5 || slots[y][x+4])
                        return true;
                    break;
            }
            break;
        }
        case 3:
        {
            switch(state)
            {
			case 0:case 2:
                    if(x>6 || slots[y][x+2] || slots[y+1][x+3])
                        return true;
                    break;
                default:
                    if(x>7 || slots[y][x+2] || slots[y+1][x+2] || slots[y+2][x+1])
                        return true;
                    break;
            }
            break;
        }
        case 4:
        {
            switch(state)
            {
			case 0:case 2:
                    if(x>6 || slots[y][x+3] || slots[y+1][x+2])
                        return true;
                    break;
                default:
                    if(x>7 || slots[y][x+1] || slots[y+1][x+2] || slots[y+2][x+2])
                        return true;
                    break;
            }
            break;
        }
        case 5:
        {
            switch(state)
            {
                case 0:
                    if(x>7 || slots[y][x+1] || slots[y+1][x+1] || slots[y+2][x+2])
                        return true;
                    break;
                case 1:
                    if(x>6 || slots[y][x+3] || slots[y+1][x+1])
                        return true;
                    break;
                case 2:
                    if(x>7 || slots[y][x+2] || slots[y+1][x+2] || slots[y+2][x+2])
                        return true;
                    break;
                default:
                    if(x>6 || slots[y][x+3] || slots[y+1][x+3])
                        return true;
                    break;
            }
            break;
        }
        default:
        {
            switch(state)
            {
                case 0:
                    if(x>7 || slots[y][x+2] || slots[y+1][x+2] || slots[y+2][x+2])
                        return true;
                    break;
                case 1:
                    if(x>6 || slots[y][x+1] || slots[y+1][x+3])
                        return true;
                    break;
                case 2:
                    if(x>7 || slots[y][x+2] || slots[y+1][x+1] || slots[y+2][x+1])
                        return true;
                    break;
                default:
                    if(x>6 || slots[y][x+3] || slots[y+1][x+3])
                        return true;
                    break;
            }
            break;
        }
    }
    return false;
}
bool Board::checkCollisionWithLeftWall()
{
    switch(shape)
    {
        case 0:
            switch(state)
            {
                case 0:
                    if(x < 1 || slots[y+1][x-1] || slots[y][x])
                        return true;
                    break;
                case 1:
                    if(x < 0 || slots[y][x] || slots[y+1][x] || slots[y+2][x])
                        return true;
                    break;
                case 2:
                    if(x < 1 || slots[y+1][x-1] || slots[y+2][x])
                        return true;
                    break;
                case 3:
                    if(x < 1 || slots[y][x] || slots[y+1][x-1] || slots[y+2][x])
                        return true;
                    break;
            }
            break;
        case 1:
               default:
                    if(x<1 || slots[y][x-1] || slots[y+1][x-1])
                        return true;
                    break;
            break;
        case 2:
            switch(state)
            {
			case 0:case 2:
                    if(x<1 || slots[y][x-1] || slots[y+1][x-1] || slots[y+2][x-1] || slots[y+3][x-1])
                        return true;
                    break;
                default:
                    if(x<1 || slots[y][x-1])
                        return true;
                    break;
            }
            break;
        case 3:
            switch(state)
            {
			case 0: case 2:
                    if(x<1 || slots[y][x-1] || slots[y+1][x])
                        return true;
                    break;
                default:
                    if(x<1 || slots[y][x] || slots[y+1][x-1] || slots[y+2][x-1])
                        return true;
                    break;
            }
            break;
        case 4:
            switch(state)
            {
			case 0:case 2:
                    if(x<1 || slots[y+1][x-1] || slots[y][x])
                        return true;
                    break;
                default:
                    if(x<1 || slots[y][x-1] || slots[y+1][x-1] || slots[y+2][x])
                        return true;
                    break;
            }
            break;
        case 5:
            switch(state)
            {
                case 0:
                    if(x<1 || slots[y][x-1] || slots[y+1][x-1] || slots[y+2][x-1])
                        return true;
                    break;
                case 1:
                    if(x<1 || slots[y][x-1] || slots[y+1][x-1])
                        return true;
                    break;
                case 2:
                    if(x<1 || slots[y][x-1] || slots[y+1][x] || slots[y+2][x])
                        return true;
                    break;
                case 3:
                    if(x<1 || slots[y][x+1] || slots[y+1][x-1])
                        return true;
                    break;
            }
            break;
        case 6:
            switch(state)
            {
                case 0:
                    if(x<1 || slots[y][x] || slots[y+1][x] || slots[y+2][x-1])
                        return true;
                    break;
                case 1:
                    if(x<1 || slots[y][x-1] || slots[y+1][x-1])
                        return true;
                    break;
                case 2:
                    if(x<1 || slots[y][x-1] || slots[y][x-1] || slots[y][x-1])
                        return true;
                    break;
                case 3:
                    if(x<1 || slots[y][x-1] || slots[y+1][x+1])
                        return true;
                    break;
            }
            break;
    }
    return false;
}
bool Board::moveLeft()
{
    if(checkCollisionWithLeftWall())
        return false;
    x--;
    for(int i = 1;i < 10;++i)
        latitude[i-1] = latitude[i];
	latitude[9] = -1;
    return true;
}
bool Board::moveRight()
{
    if(checkCollisionWithRightWall())
        return false;
    x++;
    for(int i = 8;i >= 0;--i)
        latitude[i+1] = latitude[i];
	latitude[0] = -1;
    return true;
}
bool Board::handleInput()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:return rotate();
            case SDLK_LEFT:return moveLeft();
            case SDLK_RIGHT:return moveRight();
			case SDLK_DOWN: goDown(); return true;
			case SDLK_SPACE:while(goDown()); return true;
            default:;
        }
    }
    return false;

}
