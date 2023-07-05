#include "player.h"
#include "wasm4.h"
#include <stdint.h>

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 20
#define PLAYER_SPEED 3

void player_move_up(Player* p) {
    if (p->y >= 0) {
        p->y -= PLAYER_SPEED;
    }
}

void player_move_down(Player* p) {
    if (p->y + PLAYER_HEIGHT < 160) {
        p->y += PLAYER_SPEED;
    }
}

void player_update(Player* p, uint8_t gamepad) {
    *DRAW_COLORS = 3;
    rect(p->x, p->y, PLAYER_WIDTH, PLAYER_HEIGHT);

    p->pressedThisFrame = gamepad & (gamepad ^ p->previousGamepad);
    p->previousGamepad = gamepad;

    if (gamepad & BUTTON_UP) {
        player_move_up(p);
    } else if (gamepad & BUTTON_DOWN) {
        player_move_down(p);
    }
}
