#include "RenderView.h"
#include <cmath>

RenderView::RenderView()
{
	currentScale = 1.0;
	currentScalePower = 0;
}

void RenderView::relativeScale(const int& scalingPower)
{
	currentScalePower += scalingPower;
	currentScale = std::pow(1.1, currentScalePower); //TODO: remove magic number
}

const float& RenderView::getCurrentScale() const
{
	return currentScale;
}
