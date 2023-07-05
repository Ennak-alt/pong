#include "gameutils.h"
#include "wasm4.h"
#include "player.h"
#include "ball.h"
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

Player player1;
Player player2; 
Ball ball;

void start() {
    player1 = player_create(5, 65);
    player2 = player_create(150, 65);
    ball = ball_create(&player1, Right);
}

void update() {
    *DRAW_COLORS = 2;

    player_update(&player1, *GAMEPAD1, &ball);
    player_update(&player2, *GAMEPAD2, &ball);

    if (box_are_overlapping(ball.box, player1.box)) {
        ball_x_flip(&ball);
        trace("player1 flip");
    } else if (box_are_overlapping(ball.box, player2.box)) {
        ball_x_flip(&ball);
        trace("player2 flip");
    }

    ball_update(&ball);
}
