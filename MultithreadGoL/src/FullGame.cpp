#include "FullGame.h"
#define RENDERING_PERIOD std::chrono::microseconds(16667) //60FPS

FullGame::FullGame(const int& gridSize1, const int& gridSize2, const int& windowWidth, const int& defaultIterationDelay) :
	automata(max(gridSize1, gridSize2), min(gridSize1, gridSize2)),
	DEFAULT_ITERATION_DELAY(defaultIterationDelay),
	iterationDelay(std::chrono::milliseconds(DEFAULT_ITERATION_DELAY)),
	paused(false),
	gameSpeed(0),
	gameRunning(true),
	threadsRunning(true),
	view(windowWidth, max(gridSize1, gridSize2), min(gridSize1, gridSize2))
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
	std::chrono::steady_clock::time_point automata_last_time_measurement = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point automata_time_buffer;
	std::chrono::milliseconds automata_corrected_time;

	auto next_cycle = [this, &automata_last_time_measurement, &automata_time_buffer, &automata_corrected_time]() noexcept {
		automata.swapBuffers();
		automata_corrected_time = 2 * iterationDelay - time_elapsed(automata_last_time_measurement, automata_time_buffer);
		automata_corrected_time = min(automata_corrected_time, iterationDelay);
		std::this_thread::sleep_for(automata_corrected_time);
		threadsRunning = gameRunning;

		std::unique_lock<std::mutex> pause_lock(pauseMutex);
		if (paused) {
			pauseCondition.wait(pause_lock);
			automata_last_time_measurement = std::chrono::steady_clock::now();
		}
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

	std::chrono::steady_clock::time_point rendering_last_time_measurement = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point rendering_time_buffer;
	std::chrono::microseconds rendering_corrected_time;

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

    while (!glfwWindowShouldClose(window))
    {
		glfwPollEvents();
		if (view.getIsActivelyChanges()) {
			std::cout << "c";
			view.update(window);
			renderer.applyRendererView(view);
		}

        renderer.render();
		rendering_corrected_time = 2 * RENDERING_PERIOD - time_elapsed(rendering_last_time_measurement, rendering_time_buffer);
		rendering_corrected_time = min(rendering_corrected_time, RENDERING_PERIOD);
		std::this_thread::sleep_for(rendering_corrected_time);
    }
	gameRunning = false;

	for (int i = 0; i < num_threads; i++) {
		threads[i].join();
	}
}

void FullGame::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	FullGame* game_instance = static_cast<FullGame*>(glfwGetWindowUserPointer(window));
	game_instance->view.relativeScale(yoffset);
	game_instance->renderer.applyRendererView(game_instance->view);
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
			game_instance->pauseCondition.notify_one();
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		}
	}
}

void FullGame::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	FullGame* game_instance = static_cast<FullGame*>(glfwGetWindowUserPointer(window));
	
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
		game_instance->view.mouseShiftStart(window);
		std::cout << "pressed\n";
	}
	else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
		game_instance->view.mouseShiftEnd();
		std::cout << "unpressed\n";
	}
}


