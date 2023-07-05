#include "wasm4.h"
#include "player.h"
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include <stdlib.h>

// Remember to do this a bit better
Player p1;
Player p2; 

void start() {
    Player p1 = player_create(2, 65);
    Player p2 = player_create(153, 65);
}

void update() {
    *DRAW_COLORS = 2;

    player_update(&p1, *GAMEPAD1);
    player_update(&p2, *GAMEPAD2);
}
