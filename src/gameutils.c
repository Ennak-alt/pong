#import "gameutils.h"

Box box_create(int x, int y, int width, int height) {
    Box b = {
        .x = x,
        .y = y,
        .width = width,
        .height = height
    };
    return b;
}