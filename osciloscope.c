#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include "helpers.h"
#include "serial_port.h"

#define BUFF_SIZE 500
bool active = true;

int buffer1[BUFF_SIZE];
int buffer2[BUFF_SIZE];

pthread_mutex_t mutex;

typedef struct {
    int *buffer;
    float zoom;
    unsigned int time;
} PLOT_ARGS_T;

void *plot_t(void *args){

    PLOT_ARGS_T *argsx = (PLOT_ARGS_T *) args;
    int j = 0;

    while(active) {
	j++;

	pthread_mutex_lock(&mutex);
        
	for (int i = 0; i < BUFF_SIZE; i++) {
            argsx->buffer[i] = (1 + sin(2 * M_PI * 1/argsx->zoom * i + (double)j / 10) * sin(M_PI * i + (double)j/10)) * 512;
        }
        
        clear();
        move(LINES / 2, 0);
        hline(ACS_HLINE, COLS);
        plot(UP, buffer1, BUFF_SIZE);
        plot(DOWN, buffer2, BUFF_SIZE);
        refresh();

        pthread_mutex_unlock (&mutex);

        usleep(argsx->time);
    }

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex, NULL);

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    PLOT_ARGS_T args1 = { buffer1, 120.0, 19000};
    pthread_t t1;
    int i1 = pthread_create(&t1, NULL, plot_t, &args1);

    PLOT_ARGS_T args2 = { buffer2, 100.0, 10000};
    pthread_t t2;
    int i2 = pthread_create(&t2, NULL, plot_t, &args2);

    while(getch() != 'q') {;}

    active = false;
    int result_code = pthread_join(t1, NULL);
    assert( !result_code );
    result_code = pthread_join(t2, NULL);
    assert( !result_code );

    endwin();

    pthread_mutex_destroy(&mutex);
    return 0;
}
