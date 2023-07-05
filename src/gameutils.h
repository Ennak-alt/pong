#ifndef GAMEUTILS
#define GAMEUTILS

typedef struct Box{
    int x;
    int y;
    int width;
    int height;
} Box;

Box box_create(int x, int y, int width, int height);
#endif