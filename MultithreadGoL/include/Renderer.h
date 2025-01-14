#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <windows.h>
#include "RenderView.h"
#include "GameOfLife.h"


class Renderer
{
public:
	Renderer(GLFWwindow* window, GameOfLife* gameToRender);
	Renderer();
	Renderer& operator=(const Renderer& other);
	void render();
	void applyRendererView(const RenderView& view);

private:
	GLFWwindow* window;
	GameOfLife* gameToRender;
	void feelSSBO();
	float reversedCellSize;
	int ssbo_size;
	
	GLuint shaderProgram;
	GLuint ssbo_front;
	GLuint dummyVAO;

	GLuint reversed_cell_size_uniform;
	GLuint current_scale_uniform;
	GLuint grid_size_uniform;
	GLuint view_shift_uniform;

	friend class FullGame;
};
