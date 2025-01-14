#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class RenderView
{
public:
	RenderView(const int& windowWidth, const int& gridWidth, const int& gridHeight);
	//void relativeShift(const float& shiftX, const float& shiftY);
	void update(GLFWwindow* window);
	void mouseShiftStart(GLFWwindow* window);
	void mouseShiftUpdate(GLFWwindow* window);
	void mouseShiftEnd();
	void setAbsolutePosition(const float& positionX, const float& positionY);
	void relativeScale(const int& scalingPower);
	void viewShift(const float& shiftX, const float& shiftY);

	const bool& cellValueUnderViewIndex(const int& viewIndex, bool* cells) const;
	int viewIndexToRenderIndex(int viewIndex);
	int cellIndexFromMouse(GLFWwindow* window);

	const float& getAbsolutePositionX() const;
	const float& getAbsolutePositionY() const;
	const float& getCurrentScale() const;
	const bool& getIsActivelyChanges() const;

private:
	void updateTransform();
	void applyMouseShift();
	int windowWidth, gridWidth, gridHeight;
	float absolutePositionX, absolutePositionY, oldAbsolutePositionX, oldAbsolutePositionY;
	double startingCursorPositionX, startingCursorPositionY, pressedCursorPositionX, pressedCursorPositionY;
	int viewGridPositionX, viewGridPositionY;
	float residualShiftX, residualShiftY;
	float currentScale;
	int currentScalePower;
	bool isActivelyChanges;
};

