#include "gameutils.h"
#include "wasm4.h"
#include "player.h"
#include "ball.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

enum menu {
    AGAIN,
    BACK,
};

enum gameState {
    SINGLEPLAYER,
    MULTIPLAYER,
    STARTMENU,
};

Player player1;
Player player2; 
Ball ball;
bool gameIsDone;
enum menu menu;
int lstGamepad;
int frame;
uint8_t computerGamePad;
enum gameState gameState;

char score1[3];
char score2[3];

void start() {
    player1 = player_create(3, 80);
    player1.box.y -= player1.box.height/2;
    player2 = player_create(155, 80);
    player2.box.y -= player2.box.height/2;
    ball = ball_create(&player1, Right);
    menu = AGAIN;
    lstGamepad = *GAMEPAD1;
    gameIsDone = false;
    frame = 0;
    gameState = STARTMENU;
}

void convert2DigNumToStr(int num, char* buffer) {
    if (num >= 10) {
        *buffer++ = '1';
        num -= 10;
    }
    *buffer++ = (char)(num + 48);
    *buffer = '\0'; 
}

enum smenu {
    SING,
    MULT
};

enum smenu smenu = SING;

void startMenu() {
    *DRAW_COLORS = 3;
    int pressed = *GAMEPAD1 & (*GAMEPAD1 ^ lstGamepad);
    if (smenu == SING) {
        oval(15, 68, 10, 10);
        if (pressed & BUTTON_DOWN) {
            smenu = MULT;
        } else if (pressed & BUTTON_1) {
            start();
            gameState = SINGLEPLAYER;
        } 
    } else {
        oval(15, 88, 10, 10);
        if (pressed & BUTTON_UP) {
            smenu = SING;
        } else if (pressed & BUTTON_1) {
            start();
            gameState = MULTIPLAYER;
        } 
    }

    *DRAW_COLORS = 2;

    text("PONG!", 55, 50);

    text("Singleplayer", 32, 70);

    text("Multiplayer", 35, 90);

}

void singleplayer() {
    *DRAW_COLORS = 1;
    text("hell", 20, 20);
    if (player1.score == 11) {
        *DRAW_COLORS = 2;
        text("You won!", 50, 65);
        gameIsDone = true;
        return;
    } else if (player2.score == 11) {
        *DRAW_COLORS = 2;
        text("You lost!", 50, 65);
        gameIsDone = true;
        return;
    }

    computerGamePad = 0;
    
    player_update(&player1, *GAMEPAD1, &ball);
    if (frame == 2) {
        frame = 0;
    }
    if (ball.playerPtr != NULL) {
        computerGamePad |= BUTTON_1;
    }
    if (ball.box.y < player2.box.y && frame == 0) {
        computerGamePad |= BUTTON_UP;
        frame = 0;
    } else if (ball.box.y > player2.box.y && frame == 0) {
        computerGamePad |= BUTTON_DOWN;
        frame = 0;
    }
    frame++;

    player_update(&player2, computerGamePad, &ball);
}

void multiplayer() {
    if (player1.score == 11) {
        *DRAW_COLORS = 2;
        text("Player 1 won!", 30, 70);
        gameIsDone = true;
        return;
    } else if (player2.score == 11) {
        *DRAW_COLORS = 2;
        text("Player 2 won!", 30, 70);
        gameIsDone = true;
        return;
    }
    
    player_update(&player1, *GAMEPAD2, &ball);
    player_update(&player2, *GAMEPAD1, &ball);
}

void gameLogic() {
    if (gameIsDone) {
        return;
    }
    ball_update(&ball);

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

    ball_render(&ball);
    player_render(&player1);
    player_render(&player2);

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

void endmenu() {
    if (gameIsDone) {
        *DRAW_COLORS = 2;
        text("Wanna play again?", 15, 80);
        text("Yes", 30, 100);
        text("No", 110, 100);

        int pressed = *GAMEPAD1 & (*GAMEPAD1 ^ lstGamepad);

        if (menu == AGAIN) {
            *DRAW_COLORS = 2;
            hline(30, 110, 25);
            if (pressed & BUTTON_RIGHT) {
                menu = BACK;
            } else if (pressed & BUTTON_1) {
                enum gameState tmp = gameState;
                start();
                gameState = tmp;
            } 
        } else {
            *DRAW_COLORS = 2;
            hline(105, 110, 25);
            if (pressed & BUTTON_LEFT) {
                menu = AGAIN;
            }
            else if (pressed & BUTTON_1) {
                gameState = STARTMENU;    
            }
        }
        return;
    }
}

void update() {
    *DRAW_COLORS = 1;
    rect(0, 0, 160, 160);
    switch (gameState) {
        case STARTMENU:
            startMenu();
            break;
        case MULTIPLAYER:
            multiplayer();
            gameLogic();
            endmenu();
            break;
        case SINGLEPLAYER:
            singleplayer();
            gameLogic();
            endmenu();
            break;
    }
    lstGamepad = *GAMEPAD1;
}
