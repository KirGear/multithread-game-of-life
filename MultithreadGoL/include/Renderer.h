#pragma once
#include "GameOfLife.h"

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <windows.h>

//#include "vertexShaderSource.h"
//#include "fragmentShaderSource.h"
#include <format>
//#include "RenderView.h"


class Renderer
{
public:
	Renderer(GLFWwindow* window, GameOfLife* gameToRender);
	Renderer();
	//~Renderer();
	Renderer& operator=(const Renderer& other);
	void render();

	//RenderView view;

private:
	GLFWwindow* window;
	GameOfLife* gameToRender;
	void feelSSBO();
	float cellSize;
	
	GLuint shaderProgram;
	GLuint ssbo_front;
	GLuint dummyVAO;

	GLuint reversed_cell_size_uniform;
	GLuint grid_width_uniform;
};