#include "helpers.h"
#include <ncurses.h>

void plot(PanelLoc_t p, int * data_set, int set_size) {
    int cols = set_size;
    if (COLS < cols) cols = COLS;

    for(int i = 0; i < cols; i++) {
        int val = normalize(data_set[i]);
        int offset = get_offset(p);
        move(val + offset, i);
        addch(ACS_DIAMOND);
    }
}

int normalize(int value) {
    return (int)(((float) value / 1023.0) * ((LINES / 2) - 2));
}

int get_offset(PanelLoc_t p) {
    int offset = 0;
    if (p == UP) offset = 1;
    else if (p == DOWN) offset = 1 + LINES/2;
    return offset;
}