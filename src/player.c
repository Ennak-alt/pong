#include "player.h"
#include "ball.h"
#include "wasm4.h"
#include <stdint.h>

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 15
#define PLAYER_SPEED 3

Player player_create(int x, int y) {
    Player p = {
        .box = box_create(x, y, PLAYER_WIDTH, PLAYER_HEIGHT),
        .score = 0,
    };
    Box b = box_create(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
    return p;
}

void player_move_up(Player* p) {
    if (p->box.y >= 0) {
        p->box.y -= PLAYER_SPEED;
    }
}

void player_move_down(Player* p) {
    if (p->box.y + (int)p->box.height < 160) {
        p->box.y += PLAYER_SPEED;
    }
}

void player_update(Player* p, uint8_t gamepad, Ball* ball) {
    *DRAW_COLORS = 3;

    rect(p->box.x, p->box.y, PLAYER_WIDTH, PLAYER_HEIGHT);

    p->pressedThisFrame = gamepad & (gamepad ^ p->previousGamepad);
    p->previousGamepad = gamepad;

    if (gamepad & BUTTON_UP) {
        player_move_up(p);
    } else if (gamepad & BUTTON_DOWN) {
        player_move_down(p);
    }

    if (p->pressedThisFrame & BUTTON_1 && ball->playerPtr == p) {
        ball_launch(ball);
    }
}
