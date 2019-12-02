/*
  ==============================================================================

    SodaRectBrush.cpp
    Created: 2 Dec 2019 9:31:03pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaBrush.h"

void FSodaRectBrush::startDraw(Image * image, const Point<float>& CurrentPixelUnderMouse)
{
	FSodaBrush::startDraw(image, CurrentPixelUnderMouse);
	originPoint = CurrentPixelUnderMouse;
}

void FSodaRectBrush::updateDraw(Image * image, const Point<float>& CurrentPixelUnderMouse)
{
	if (!FSodaBrush::preUpdateDraw(CurrentPixelUnderMouse)) return;

	auto Vector = CurrentPixelUnderMouse - originPoint;
	resetPixels(image);

	float RectHalfWidth = abs(Vector.x);
	float RectHalfHeight = abs(Vector.y);

	//draw from left to right (in bottom and top line)
	for (float i = -RectHalfWidth; i <= RectHalfWidth; i += 0.5f)
	{
		//y - halfheight row
		drawPixel(image,
			originPoint.x + i,
			originPoint.y - RectHalfHeight,
			gProperties.brushSize,
			gProperties.brushColour);

		//y + halfheight row
		drawPixel(image,
			originPoint.x + i,
			originPoint.y + RectHalfHeight,
			gProperties.brushSize,
			gProperties.brushColour);
	}
	
	//draw the Colu
	for (float i = -RectHalfHeight; i <= RectHalfHeight; i += 0.5f)
	{
		//x - halfwidth column
		drawPixel(image,
			originPoint.x - RectHalfWidth,
			originPoint.y + i,
			gProperties.brushSize,
			gProperties.brushColour);

		//x + halfwidth column
		drawPixel(image,
			originPoint.x + RectHalfWidth,
			originPoint.y + i,
			gProperties.brushSize,
			gProperties.brushColour);
	}
}
