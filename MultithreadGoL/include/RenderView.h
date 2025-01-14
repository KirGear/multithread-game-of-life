#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class RenderView
{
public:
	RenderView(const int& windowWidth, const int& gridWidth, const int& gridHeight);
	void update(GLFWwindow* window);
	void mouseShiftStart(GLFWwindow* window);
	void mouseShiftUpdate(GLFWwindow* window);
	void mouseShiftEnd();
	void setAbsolutePosition(const float& positionX, const float& positionY);
	void relativeScale(const int& scalingPower);
	void viewShift(const float& shiftX, const float& shiftY);

	const float& getAbsolutePositionX() const;
	const float& getAbsolutePositionY() const;
	const float& getCurrentScale() const;
	const bool& getIsActivelyChanges() const;

private:
	int windowWidth, gridWidth, gridHeight;
	float absolutePositionX, absolutePositionY, oldAbsolutePositionX, oldAbsolutePositionY;
	double startingCursorPositionX, startingCursorPositionY, pressedCursorPositionX, pressedCursorPositionY;
	float currentScale;
	int currentScalePower;
	bool isActivelyChanges;
};

