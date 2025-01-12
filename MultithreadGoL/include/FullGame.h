#pragma once
#include <cmath>
#include "GameOfLife.h"
#include "Renderer.h"
#include "RenderView.h"
#include <chrono>
#include <iostream>
#include <barrier>
#include <thread>

class FullGame
{
public:
	FullGame(const int& gridSize1, const int& gridSize2, const int& windowWidth, const int& defaultIterationDelay);
	//TODO destructor with glfwTerminate();
	GLFWwindow* window; //TODO consider private???
	void run(const int& num_threads);
	 //TODO private
private:
	GameOfLife automata;
	Renderer renderer;
	RenderView view;
	bool paused;
	int gameSpeed;
	const int DEFAULT_ITERATION_DELAY;
	std::chrono::milliseconds iterationDelay;
	bool drawColor;
	void handleEvents();
	void updateIterationDelay();
	void draw();
	void tryDraw();
	bool gameRunning;
	bool threadsRunning;

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

