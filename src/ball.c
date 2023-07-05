#import "ball.h"
#import "gameutils.h"
#import <stdlib.h>
#import <stdbool.h>
#import "wasm4.h"

#define BALL_WIDTH 4
#define BALL_HEIGHT 4

void ball_stick_to_player(Ball *b) {
    if (b->side == Right) {
        b->box.x = b->playerPtr->box.x+(int)b->playerPtr->box.width; 
    } else {
        b->box.x = b->playerPtr->box.x-BALL_WIDTH;
    }
    b->box.y = b->playerPtr->box.y+(int)b->playerPtr->box.height/2-BALL_HEIGHT/2; 
}

Ball ball_create(Player* p, enum side s) {
    Box box; 
    if (s == Right) {
        box = box_create(0, 0, BALL_WIDTH, BALL_HEIGHT);     
    } else {
        box = box_create(0, 0, BALL_WIDTH, BALL_HEIGHT);     
    }    
    Ball ball = {
        .box = box,
        .playerPtr = p
    };
    ball_stick_to_player(&ball);
    return ball;
}

void ball_launch(Ball *b) {
    b->playerPtr = NULL;
}

void ball_update(Ball* b) {
    if (b->playerPtr) {
        ball_stick_to_player(b);
    } else {
        b->box.x += b->xdir;        
        b->box.y += b->ydir;
    }
    oval(b->box.x, b->box.y, b->box.width, b->box.height);
}

void ball_x_flip(Ball* b) {
    b->xdir *= -1;
}

void ball_y_flip(Ball* b) {
    b->ydir *= -1;
}

bool ball_has_hit_side(Ball *b, Player* lp, Player* rp) {
    if (b->box.x == 160) {
        lp->score++;
        return true;
    } else if (b->box.x == 0) {
        rp->score++;
        return true;
    } 
    return false;
}