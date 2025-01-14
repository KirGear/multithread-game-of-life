#pragma once
#include <cmath>
#include "GameOfLife.h"
#include "Renderer.h"
#include "RenderView.h"
#include "utils.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <barrier>
#include <condition_variable>

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
	void updateIterationDelay();
	void draw();
	void tryDraw();
	bool gameRunning;
	bool threadsRunning;
	std::mutex automataChangeMutex;
	std::mutex pauseMutex;
	std::condition_variable pauseCondition;

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
};

