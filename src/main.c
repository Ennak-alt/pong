#include "gameutils.h"
#include "wasm4.h"
#include "player.h"
#include "ball.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>

Player player1;
Player player2; 
Ball ball;

char score1[3];
char score2[3];

void start() {
    player1 = player_create(3, 65);
    player2 = player_create(155, 65);
    ball = ball_create(&player1, Right);
}

void player_ball_collision(Ball* ball, Player* player) {
    if (box_are_overlapping(ball->box, player->box)) {
        ball_x_flip(ball);
        int midPlayer = player->box.y + player->box.height/2;
        int midBall = ball->box.y + ball->box.height/2;
        if ((midBall > midPlayer && ball->ydir == -1) || 
            (midBall < midPlayer && ball->ydir == 1)) {
            ball_y_flip(ball);
        } 
    }
}

void convert2DigNumToStr(int num, char* buffer) {
    if (num >= 10) {
        *buffer++ = '1';
        num -= 10;
    }
    *buffer++ = (char)(num + 48);
    *buffer = '\0'; 
}

void update() {

    ball_update(&ball);
    player_update(&player1, *GAMEPAD2, &ball);
    player_update(&player2, *GAMEPAD1, &ball);

    player_ball_collision(&ball, &player1);
    player_ball_collision(&ball, &player2);

    if (ball_has_hit_side(&ball, &player1, &player2)){
        if (ball.box.x <= 0) {
            ball = ball_create(&player1, Right);
        } else {
            ball = ball_create(&player2, Left);
        }
    }

    *DRAW_COLORS = 2;
    convert2DigNumToStr(player1.score, score1);
    convert2DigNumToStr(player2.score, score2);

    text(score1, 65 - (player1.score >= 10 ? 10 : 0), 20);
    text("10", 89, 20);

    vline(80, 17, 13);
}
