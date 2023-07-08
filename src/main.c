#include "gameutils.h"
#include "wasm4.h"
#include "player.h"
#include "ball.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

Player player1;
Player player2; 
Ball ball;

char score1[3];
char score2[3];

void start() {
    player1 = player_create(3, 80);
    player1.box.y -= player1.box.height/2;
    player2 = player_create(155, 80);
    player2.box.y -= player2.box.height/2;
    ball = ball_create(&player1, Right);
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

    ball_player_collision(&ball, &player1);
    ball_player_collision(&ball, &player2);

    if (ball_has_hit_side(&ball, &player1, &player2)){
        tone(150, 10, 50, TONE_PULSE1);
        if (ball.box.x <= 0) {
            ball = ball_create(&player1, Right);
        } else {
            ball = ball_create(&player2, Left);
        }
    }

    *DRAW_COLORS = 2;
    convert2DigNumToStr(player1.score, score1);
    convert2DigNumToStr(player2.score, score2);

    text(score1, 64 - (player1.score >= 10 ? 10 : 0), 10);
    text(score2, 90, 10);

    for (int i = 2; i < 160; i += 4) {
        vline(80, i, 4);
        i += 4;
    }

    hline(0, 0, 160);
    hline(0, 1, 160);
    hline(0, 2, 160);

    hline(0, 157, 160);
    hline(0, 158, 160);
    hline(0, 159, 160);
}
