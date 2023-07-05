#include "wasm4.h"
#include "player.h"
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include <stdlib.h>

// Remember to do this a bit better
Player p1 = {.x = 2, .y = 65};
Player p2 = {.x = 153, .y = 65};

void update () {
    *DRAW_COLORS = 2;

    player_update(&p1, *GAMEPAD1);
    player_update(&p2, *GAMEPAD2);

}
