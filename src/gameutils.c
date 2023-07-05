#import "gameutils.h"
#import <stdbool.h>

Box box_create(int x, int y, int width, int height) {
    Box b = {
        .x = x,
        .y = y,
        .width = width,
        .height = height
    };
    return b;
}

bool is_in_box(Box b, int x, int y) {
    return  b.x <= x && b.x+b.width >= x && 
            b.y <= y && b.y+b.height >= y;
}

bool box_are_overlapping(Box b1, Box b2) {
    int b2L = b1.x, b2R = b1.x+b1.width, b2T = b1.y, b2B = b1.y+b1.height;
    return  is_in_box(b1, b2L, b2T) || 
            is_in_box(b1, b2L, b2B) ||
            is_in_box(b1, b2R, b2T) ||
            is_in_box(b1, b2R, b2B);
}