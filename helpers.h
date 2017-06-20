#ifndef HELPERS_H
#define HELPERS_H

typedef enum {
    UP, DOWN
} PanelLoc_t;

void plot(PanelLoc_t p, int * data_set, int set_size);

int normalize(int value);

int get_offset(PanelLoc_t p);

#endif /* HELPERS_H */