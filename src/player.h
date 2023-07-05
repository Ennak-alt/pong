#ifndef PLAYER
#define PLAYER

#include <stdint.h>
typedef struct Player {
    int x;
    int y; 
    uint8_t previousGamepad;
    uint8_t pressedThisFrame;
} Player;

void player_update(Player*, uint8_t);

#endif