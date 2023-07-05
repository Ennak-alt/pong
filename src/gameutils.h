#ifndef GAMEUTILS
#define GAMEUTILS

#include <stdbool.h>
#include <stdint.h>
typedef struct Box{
    int x;
    int y;
    int width;
    int height;
} Box;

enum side {Right, Left};

Box box_create(int x, int y, int width, int height);

bool box_are_overlapping(Box, Box);
#endif