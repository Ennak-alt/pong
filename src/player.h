#ifndef PLAYER
#define PLAYER

#include <stdint.h>
#include "gameutils.h"
typedef struct Player {
    Box box;
    uint8_t score;
    uint8_t previousGamepad;
    uint8_t pressedThisFrame;
} Player;

Player player_create(int x, int y);
void player_update(Player*, uint8_t);

#endif