#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

//Game state base class
class GameState
{
public:
    virtual void handle_events() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    virtual ~GameState(){};
};

#endif // GAMESTATE_H_INCLUDED