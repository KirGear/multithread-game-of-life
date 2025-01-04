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
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        Sleep(100);
        renderer.render();
        automata.update();

        glfwPollEvents();
    }
}
