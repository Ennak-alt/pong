#include <stdlib.h>
#include <stdbool.h>
#include "wasm4.h"
#include "ball.h"

#define BALL_WIDTH 2
#define BALL_HEIGHT 2

void ball_stick_to_player(Ball *b) {
    if (b->side == Right) {
        b->box.x = b->playerPtr->box.x+(int)b->playerPtr->box.width+1; 
    } else {
        b->box.x = b->playerPtr->box.x-BALL_WIDTH-1;
    }
    b->box.y = b->playerPtr->box.y+(int)b->playerPtr->box.height/2-BALL_HEIGHT/2; 
}

Ball ball_create(Player* p, enum side s) {
    Box box; 
    int xdir;
    if (s == Right) {
        box = box_create(0, 0, BALL_WIDTH, BALL_HEIGHT);     
        xdir = 1;
    } else {
        box = box_create(0, 0, BALL_WIDTH, BALL_HEIGHT);    
        xdir = -1; 
    }    
    Ball ball = {
        .box = box,
        .playerPtr = p,
        .side = s,
        .xdir = xdir,
        .ydir = 1,
    };
    ball_stick_to_player(&ball);
    return ball;
}

void ball_launch(Ball *b) {
    tone(300, 10, 50, TONE_PULSE1);
    if (b->playerPtr->direction == UP) {
        b->ydir = -1;
    } else if (b->playerPtr->direction == DOWN) {
        b->ydir = 1;
    } else {
        b->ydir = 0;
        b->xdir *= 3;
    }
    b->playerPtr = NULL;
}

int frameCount = 0;

void ball_update(Ball* b) {
    if (frameCount == 1) {
        if (b->playerPtr) {
            ball_stick_to_player(b);
        } else {
            b->box.x += b->xdir;        
            b->box.y += b->ydir;
            if (b->box.y <= 3 || b->box.y >= 156) {
                tone(262, 5, 50, TONE_PULSE1);
                ball_y_flip(b);
            } 
        }
    } else {
        frameCount++;
    }
}

void ball_render(Ball* b) {
    *DRAW_COLORS = 3;
    oval(b->box.x, b->box.y, BALL_WIDTH, BALL_HEIGHT);
}

void ball_x_flip(Ball* b) {
    b->xdir *= -1;
}

void ball_y_flip(Ball* b) {
    b->ydir *= -1;
}

void ball_player_collision(Ball* ball, Player* player) {
    if (box_are_overlapping(ball->box, player->box)) {
        tone(262, 5, 50, TONE_PULSE1);
        ball_x_flip(ball);
        int midPlayer = player->box.y + player->box.height/2;
        int midBall = ball->box.y + ball->box.height/2;
        
        if (midBall > midPlayer) {
            ball->ydir = 1;
        } else if (midBall < midPlayer) {
            ball->ydir = -1;
        } 

        if (ball->box.x <= 10) {
            ball->box.x = player->box.x + 2;
        } else {
            ball->box.x = player->box.x - 2;
        }

        int ballOffset = abs(midPlayer - midBall);
        int xsign = ball->xdir < 0 ? -1 : 1;
        int ysign = ball->ydir < 0 ? -1 : 1;
        if (ballOffset < 2) { 
            ball->xdir = 3;
            ball->ydir = 0;
        } else if (ballOffset > 7) {
            ball->xdir = 1;
            ball->ydir = 2; 
        } else if (ballOffset >= 2 && ballOffset <= 5){
            ball->xdir = 2;
            ball->ydir = 1;
        } else {                                        
            ball->xdir = 1;
            ball->ydir = 1;
        }
        ball->xdir *= xsign;
        ball->ydir *= ysign;
    }
}

bool ball_has_hit_side(Ball *b, Player* lp, Player* rp) {
    if (b->box.x >= 160) {
        lp->score++;
        return true;
    } else if (b->box.x <= 0) {
        rp->score++;
        return true;
    } 
    return false;
}