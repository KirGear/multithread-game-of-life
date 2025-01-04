#include "RenderView.h"

RenderView::RenderView(const int& windowWidth, const int& gridWidth, const int& gridHeight, const GLuint& shaderProgram) :
	windowWidth(windowWidth), gridWidth(gridWidth), gridHeight(gridHeight), shaderProgram(shaderProgram), origCellSize(((float)windowWidth) / gridWidth) {
	if (windowWidth || gridWidth || gridHeight) {
		resolutionToCellCoefficientUniform = glGetUniformLocation(shaderProgram, "resolution_to_cells_ratio");
		glUniform2f(resolutionToCellCoefficientUniform, ((float)gridWidth)/windowWidth, 800.0); //TODO 1f cell_size_uniform
		//TODO int grid_width uniform
	}
	else {
		resolutionToCellCoefficientUniform = 0;
	}
};
