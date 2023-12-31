#ifndef PLAYER
#define PLAYER
#include <stdint.h>

#include "gameutils.h"

enum moveDir {
    UP,
    DOWN,
    STILL 
};

#pragma once
typedef struct Ball Ball;

typedef struct Player {
    Box box;
    enum moveDir direction;    
    uint8_t score;
    uint8_t previousGamepad;
    uint8_t pressedThisFrame;
} Player;

#include "ball.h"

Player player_create(int x, int y);
void player_update(Player*, uint8_t, Ball*);
void player_render(Player*);

#endif