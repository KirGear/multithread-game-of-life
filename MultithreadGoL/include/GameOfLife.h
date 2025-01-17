#pragma once
#include <random>
#include <bitset>
#include "params.h"

class GameOfLife
{
public:
    GameOfLife(const int& gridWidth, const int& gridHeight);
    ~GameOfLife();
    void update();
    void partialUpdate(const int& beginning_index, const int& ending_index);
    void swapBuffers();
    void reset();
    std::bitset<GRID_SIZE_X* GRID_SIZE_Y>* getCells();
    void clear();
    const int& getWidth() const;
    const int& getHeight() const;

private:
    int gridSizeX, gridSizeY;
    unsigned short int countNeighbours(const int& cellIndex);
    std::bitset<GRID_SIZE_X* GRID_SIZE_Y>* cells;
    std::bitset<GRID_SIZE_X* GRID_SIZE_Y>* cellsBuffer;

    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution dist;
};
