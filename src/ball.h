#ifndef BALL
#define BALL

#include <stdint.h>
#include "gameutils.h"

#pragma once
typedef struct Player Player;

typedef struct Ball {
    Box box;
    Player* playerPtr;
    enum side side;
    int xdir;
    int ydir;
} Ball;

#include "player.h"

Ball ball_create(Player*, enum side);

void ball_update(Ball*);

void ball_render(Ball*);

void ball_launch(Ball*);

void ball_x_flip(Ball*);

void ball_y_flip(Ball*);

void ball_player_collision(Ball*, Player*); 

bool ball_has_hit_side(Ball*, Player*, Player*);

#endif