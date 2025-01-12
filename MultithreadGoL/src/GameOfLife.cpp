#include "GameOfLife.h"

GameOfLife::GameOfLife(const int& gridWidth, const int& gridHeight)
{
	gridSizeX = gridWidth;
	gridSizeY = gridHeight;
	cells = new int[gridSizeY * gridSizeX];
	cellsBuffer = new int[gridSizeY * gridSizeX];

	gen.seed(rd());
	dist.param(std::bernoulli_distribution::param_type(0.3));

	reset();
}

GameOfLife::~GameOfLife()
{
	delete[] cells;
	delete[] cellsBuffer;
}

void GameOfLife::update()
{
	partialUpdate(0, gridSizeY * gridSizeX);
	std::swap(cells, cellsBuffer);
}

void GameOfLife::partialUpdate(const int& beginning_index, const int& ending_index)
{
	unsigned short int currentCellNeighboursCount;
	for (int i = beginning_index; i < ending_index; ++i) {
		currentCellNeighboursCount = countNeighbours(i);
		if (cells[i]) cellsBuffer[i] = currentCellNeighboursCount > 1 && currentCellNeighboursCount < 4;
		else cellsBuffer[i] = currentCellNeighboursCount == 3;
	}
}

void GameOfLife::swapBuffers()
{
	std::swap(cells, cellsBuffer);
}

void GameOfLife::reset()
{
	for (int i = 0; i < gridSizeY * gridSizeX; ++i) {
		cells[i] = dist(gen);
	}
}

int* GameOfLife::getCells()
{
	return cells;
}

void GameOfLife::clear()
{
	for (int i = 0; i < gridSizeY * gridSizeX; i++) {
		cells[i] = 0;
	}
}

const int& GameOfLife::getWidth() const
{
	return gridSizeX;
}

const int& GameOfLife::getHeight() const
{
	return gridSizeY;
}

unsigned short int GameOfLife::countNeighbours(const int& cellIndex)
{
	unsigned short int neighbourCount = 0;
	neighbourCount += cells[(cellIndex - gridSizeX + gridSizeY * gridSizeX) % (gridSizeY * gridSizeX)]; //up
	neighbourCount += cells[(cellIndex + gridSizeX) % (gridSizeY * gridSizeX)]; //down
	neighbourCount += cells[(cellIndex % gridSizeX) ? cellIndex - 1 : cellIndex - 1 + gridSizeX]; //left
	neighbourCount += cells[((cellIndex + 1) % gridSizeX) ? cellIndex + 1 : cellIndex + 1 - gridSizeX]; //right

	neighbourCount += cells[(cellIndex % gridSizeX) ?
		(cellIndex - 1 - gridSizeX + gridSizeY * gridSizeX) % (gridSizeY * gridSizeX) :
		(cellIndex - 1 + gridSizeY * gridSizeX) % (gridSizeY * gridSizeX)]; //left up

	neighbourCount += cells[(cellIndex % gridSizeX) ?
		(cellIndex - 1 + gridSizeX) % (gridSizeY * gridSizeX) :
		(cellIndex - 1 + 2 * gridSizeX) % (gridSizeY * gridSizeX)]; //left down

	neighbourCount += cells[((cellIndex + 1) % gridSizeX) ?
		(cellIndex + 1 - gridSizeX + gridSizeY * gridSizeX) % (gridSizeY * gridSizeX) :
		(cellIndex + 1 - 2 * gridSizeX + gridSizeY * gridSizeX) % (gridSizeY * gridSizeX)]; //right up

	neighbourCount += cells[((cellIndex + 1) % gridSizeX) ?
		(cellIndex + 1 + gridSizeX) % (gridSizeY * gridSizeX) :
		(cellIndex + 1) % (gridSizeY * gridSizeX)]; //right down

	return neighbourCount;
}
