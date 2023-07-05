#ifndef GAMEUTILS
#define GAMEUTILS

#include <stdint.h>
typedef struct Box{
    int x;
    int y;
    uint32_t width;
    uint32_t height;
} Box;

enum side {Right, Left};

Box box_create(int x, int y, uint32_t width, uint32_t height);
#endif