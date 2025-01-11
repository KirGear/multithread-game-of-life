#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class RenderView
{
public:
	RenderView();
	RenderView(const int& windowWidth, const int& gridWidth, const int& gridHeight, const GLuint& shaderProgram);
	//void relativeShift(const float& shiftX, const float& shiftY);
	void mouseShiftStart(GLFWwindow* window);
	void mouseShiftUpdate(GLFWwindow* window);
	void mouseShiftEnd();
	void setAbsolutePosition(const float& positionX, const float& positionY);
	void relativeScale(const int& scalingPower);
	void viewShift(const float& shiftX, const float& shiftY);

	const bool& cellValueUnderViewIndex(const int& viewIndex, bool* cells) const;
	int viewIndexToRenderIndex(int viewIndex);
	int cellIndexFromMouse(GLFWwindow* window);

	const int& getViewGridPositionX() const;
	const int& getViewGridPositionY() const;
	const int& getViewGridWidth() const;
	const int& getViewGridHeight() const;
	const float& getCurrentScale() const;

private:
	void updateTransform();
	void applyMouseShift(GLFWwindow* window);
	int windowWidth, gridWidth, gridHeight;
	float absolutePositionX, absolutePositionY, oldAbsolutePositionX, oldAbsolutePositionY;
	int viewGridPositionX, viewGridPositionY;
	float residualShiftX, residualShiftY;
	float currentScale;
	int currentScalePower;
	int viewGridWidth, viewGridHeight;
	bool mouseActive;
	//Vector2i originalMousePosition;
	//const float origCellSize;
	//Transform currentViewTransform;

	float resolutionToCellCoefficientX, resolutionToCellCoefficientY;
};

