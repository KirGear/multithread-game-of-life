#include "RenderView.h"
#include <cmath>


RenderView::RenderView(const int& windowWidth, const int& gridWidth, const int& gridHeight):
	currentScale(1.0),
	currentScalePower(0),
	isActivelyChanges(false),
	windowWidth(windowWidth),
	gridWidth(gridWidth), gridHeight(gridHeight),
	absolutePositionX(0.0), absolutePositionY(0.0)
{
}

void RenderView::update(GLFWwindow* window)
{
	mouseShiftUpdate(window);
}

void RenderView::mouseShiftStart(GLFWwindow* window)
{
	isActivelyChanges = true;
	oldAbsolutePositionX = absolutePositionX;
	oldAbsolutePositionY = absolutePositionY;
	glfwGetCursorPos(window, &startingCursorPositionX, &startingCursorPositionY);
}

void RenderView::mouseShiftUpdate(GLFWwindow* window)
{
	glfwGetCursorPos(window, &pressedCursorPositionX, &pressedCursorPositionY);

	setAbsolutePosition(oldAbsolutePositionX -
											(pressedCursorPositionX - startingCursorPositionX) * currentScale,
						oldAbsolutePositionY -
											(pressedCursorPositionY - startingCursorPositionY) * currentScale);
}

void RenderView::mouseShiftEnd()
{
	isActivelyChanges = false;
}

void RenderView::setAbsolutePosition(const float& positionX, const float& positionY)
{
	absolutePositionX = positionX - static_cast<int>(positionX / windowWidth) * windowWidth;
	if (absolutePositionX < 0) {
		absolutePositionX += windowWidth;
	}
	absolutePositionY = positionY - static_cast<int>((positionY * gridWidth) / (windowWidth * gridHeight)) * (windowWidth * gridHeight) / gridWidth;
	if (absolutePositionY < 0) {
		absolutePositionY += (windowWidth * gridHeight)/gridWidth;
	}
}

void RenderView::relativeScale(const int& scalingPower)
{
	currentScalePower += scalingPower;
	currentScale = std::pow(1.1, currentScalePower); //TODO: remove magic number
}

void RenderView::viewShift(const float& shiftX, const float& shiftY)
{
	setAbsolutePosition(absolutePositionX + shiftX, absolutePositionY + shiftY);
}

const float& RenderView::getAbsolutePositionX() const
{
	return absolutePositionX;
}

const float& RenderView::getAbsolutePositionY() const
{
	return absolutePositionY;
}

const float& RenderView::getCurrentScale() const
{
	return currentScale;
}

const bool& RenderView::getIsActivelyChanges() const
{
	return isActivelyChanges;
}
