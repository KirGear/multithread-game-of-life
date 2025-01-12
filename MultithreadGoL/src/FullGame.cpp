#include "FullGame.h"

FullGame::FullGame(const int& gridSize1, const int& gridSize2, const int& windowWidth, const int& defaultIterationDelay) :
	automata(max(gridSize1, gridSize2), min(gridSize1, gridSize2)),
	DEFAULT_ITERATION_DELAY(defaultIterationDelay),
	iterationDelay(std::chrono::milliseconds(DEFAULT_ITERATION_DELAY)),
	paused(false),
	gameSpeed(0),
	gameRunning(true),
	threadsRunning(true)
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

void FullGame::run(const int& num_threads)
{
	std::chrono::steady_clock::time_point last_time_measurement = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point time_buffer;
	std::chrono::milliseconds automata_time_correction;

	auto next_cycle = [this, &last_time_measurement, &time_buffer, &automata_time_correction]() noexcept {
		automata.swapBuffers();
		automata_time_correction = iterationDelay - time_elapsed(last_time_measurement, time_buffer);
		std::this_thread::sleep_for(iterationDelay + automata_time_correction);
		last_time_measurement = std::chrono::steady_clock::now();
		threadsRunning = gameRunning;
		};
	std::barrier sync_point(num_threads, next_cycle);

	auto partially_update_automata = [this, &sync_point](int beginning_index, int ending_index) {
		while (threadsRunning) {
			automata.partialUpdate(beginning_index, ending_index);
			sync_point.arrive_and_wait();
		}
		};

	std::vector<std::thread> threads;
	for (int i = 0; i < num_threads; i++) {
		int beginning_index = automata.getHeight() * automata.getWidth() * i / num_threads;
		int ending_index = automata.getHeight() * automata.getWidth() * (i + 1) / num_threads;
		threads.emplace_back(partially_update_automata, beginning_index, ending_index);
	}

    while (!glfwWindowShouldClose(window))
    {
		handleEvents();
		Sleep(16.7); //60FPS
        renderer.render();
    }
	gameRunning = false;

	for (int i = 0; i < num_threads; i++) {
		threads[i].join();
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
	game_instance->view.relativeScale(yoffset);
	game_instance->renderer.applyRendererView(&game_instance->view);
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
		case GLFW_KEY_SPACE:
			game_instance->paused = !game_instance->paused;
			break;
		}
	}
}


