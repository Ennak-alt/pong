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

void player_ball_collision(Ball* ball, Player* player) {
    if (box_are_overlapping(ball->box, player->box)) {
        ball_x_flip(ball);
        int midPlayer = player1.box.y+player1.box.height/2;
        int midBall = ball->box.y + ball->box.height/2;
        if ((midBall > midPlayer && ball->ydir == -1) || 
            (midBall < midPlayer && ball->ydir == 1)) {
            ball_y_flip(ball);
        } 
    }
}

void update() {
    *DRAW_COLORS = 2;

    player_update(&player1, *GAMEPAD2, &ball);
    player_update(&player2, *GAMEPAD1, &ball);

    ball_update(&ball);
    player_ball_collision(&ball, &player1);
    player_ball_collision(&ball, &player2);

    if (ball_has_hit_side(&ball, &player1, &player2)){
        if (ball.box.x <= 0) {
            ball = ball_create(&player1, Right);
        } else {
            ball = ball_create(&player2, Left);
        }
    }
}
