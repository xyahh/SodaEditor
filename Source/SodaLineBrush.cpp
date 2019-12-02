/*
  ==============================================================================

    SodaLineBrush.cpp
    Created: 2 Dec 2019 9:11:55pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaBrush.h"

void FSodaLineBrush::startDraw(Image * image, const Point<float>& CurrentPixelUnderMouse)
{
	FSodaBrush::startDraw(image, CurrentPixelUnderMouse);
	originPoint = CurrentPixelUnderMouse;
}

void FSodaLineBrush::updateDraw(Image * image, const Point<float>& CurrentPixelUnderMouse)
{
	if (!FSodaBrush::preUpdateDraw(CurrentPixelUnderMouse)) return;

	//Get straight direction from Curr Mouse position to Origin Point 
	auto Vector = PixelUnderMouse - originPoint;

	float Dist = Vector.getDistanceFromOrigin();
	Vector /= Dist;

	//redraw line
	resetPixels(image);

	//drawing all the pixels that come in the path of this vector from prev->Curr
	for (float i = 0.f; i <= Dist; i += 0.25f)
		drawPixel(image,
			originPoint.x + Vector.x * i, // X + dX
			originPoint.y + Vector.y * i, // Y + dY
			gProperties.brushSize, gProperties.brushColour);

}

