#pragma once
#include <random>

class GameOfLife
{
public:
    GameOfLife(const int& gridWidth, const int& gridHeight);
    ~GameOfLife();
    void update();
    void partialUpdate(const int& beginning_index, const int& ending_index);
    void swapBuffers();
    void reset();
    int* getCells();
    void clear();
    const int& getWidth() const;
    const int& getHeight() const;

private:
    int gridSizeX, gridSizeY;
    unsigned short int countNeighbours(const int& cellIndex);
    int* cells;
    int* cellsBuffer;

    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution dist;
};
