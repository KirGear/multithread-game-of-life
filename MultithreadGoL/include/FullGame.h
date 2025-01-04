#pragma once
#include <cmath>
#include "GameOfLife.h"
#include "Renderer.h"
#include <chrono>
#include <iostream>

class FullGame
{
public:
	FullGame(const int& gridSize1, const int& gridSize2, const int& windowWidth, const int& defaultIterationDelay);
	//TODO destructor with glfwTerminate();
	GLFWwindow* window; //TODO consider private???
	void run();
	 //TODO private
private:
	GameOfLife automata;
	Renderer renderer;
	bool paused;
	int gameSpeed;
	const int DEFAULT_ITERATION_DELAY;
	std::chrono::milliseconds iterationDelay;
	bool drawColor;
	void handleEvents();
	void updateIterationDelay();
	void draw();
	void tryDraw();
};

