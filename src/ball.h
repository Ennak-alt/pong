#ifndef BALL
#define BALL

#include "gameutils.h"
#include "player.h"
typedef struct Ball {
    Box box;
    Player* playerPtr;
    enum side side;
    int xdir;
    int ydir;
} Ball;

Ball ball_create(Player*, enum side);

void ball_update(Ball*);

void ball_x_flip(Ball*);

void ball_y_flip(Ball*);

#endif