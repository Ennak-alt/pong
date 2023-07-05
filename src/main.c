#include "wasm4.h"
#include "player.h"
#include "ball.h"
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// Remember to do this a bit better
Player p1;
Player p2; 
Ball b;

void start() {
    p1 = player_create(5, 65);
    p2 = player_create(150, 65);
    b = ball_create(&p1, Right);
}

void update() {
    *DRAW_COLORS = 2;

    player_update(&p1, *GAMEPAD1);
    player_update(&p2, *GAMEPAD2);
    ball_update(&b);
}
