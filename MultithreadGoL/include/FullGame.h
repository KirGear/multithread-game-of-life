#pragma once
#include <chrono>
#include <iostream>
#include <thread>
#include <barrier>
#include <condition_variable>
#include "GameOfLife.h"
#include "Renderer.h"
#include "RenderView.h"
#include "utils.h"

class FullGame
{
public:
	FullGame(const int& gridSize1, const int& gridSize2, const int& windowWidth, const int& defaultIterationDelay);
	void run(const int& num_threads);
private:
	GLFWwindow* window;
	GameOfLife automata;
	Renderer renderer;
	RenderView view;
	bool paused;
	int gameSpeed;
	const int DEFAULT_ITERATION_DELAY;
	int iterationDelayPower;
	std::chrono::milliseconds iterationDelay;
	bool drawColor;
	void changeIterationDelay(const int& change_power);
	bool gameRunning;
	bool threadsRunning;
	std::mutex automataChangeMutex;
	std::mutex pauseMutex;
	std::condition_variable pauseCondition;

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
};

