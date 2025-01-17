#include "FullGame.h"

int main()
{

    FullGame myfullgame(GRID_SIZE_Y, GRID_SIZE_X, WINDOW_WIDTH, SIMULATION_PERIOD);
    myfullgame.run(WORKER_THREADS_COUNT);

    return 0;
}

