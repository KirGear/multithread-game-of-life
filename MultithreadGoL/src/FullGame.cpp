#include "FullGame.h"

FullGame::FullGame(const int& gridSize1, const int& gridSize2, const int& windowWidth, const int& defaultIterationDelay) :
	automata(max(gridSize1, gridSize2), min(gridSize1, gridSize2)),
	DEFAULT_ITERATION_DELAY(defaultIterationDelay),
	iterationDelay(std::chrono::milliseconds(DEFAULT_ITERATION_DELAY)),
	paused(false),
	gameSpeed(0)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	window = glfwCreateWindow(windowWidth, (windowWidth/ automata.getWidth())*automata.getHeight(), "Game of Life", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	renderer = Renderer(window, &automata);
}

void FullGame::run()
{
    while (!glfwWindowShouldClose(window))
    {
		handleEvents();

        Sleep(DEFAULT_ITERATION_DELAY);
        renderer.render();
		automata.update();
    }
}


void FullGame::handleEvents()
{
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
}

void FullGame::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	FullGame* game_instance = static_cast<FullGame*>(glfwGetWindowUserPointer(window));
	std::cout << game_instance->renderer.reversedCellSize << "\n";
	if (yoffset > 0) {
		game_instance->renderer.reversedCellSize *= 0.9;
		glUniform1f(game_instance->renderer.reversed_cell_size_uniform, game_instance->renderer.reversedCellSize);
	}
	else if (yoffset < 0) {
		game_instance->renderer.reversedCellSize *= 1.1;
		glUniform1f(game_instance->renderer.reversed_cell_size_uniform, game_instance->renderer.reversedCellSize);
	}
}

void FullGame::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	FullGame* game_instance = static_cast<FullGame*>(glfwGetWindowUserPointer(window));
	std::cout << "pressed\n";
	if (action== GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_UP:
			std::cout << "up\n";
			glUniform2f(game_instance->renderer.view_shift_uniform, 0.0, 200.0);
			break;
		case GLFW_KEY_DOWN:
			std::cout << "down\n";
			glUniform2f(game_instance->renderer.view_shift_uniform, 0.0, 0.0);
			break;
		}
	}
}


