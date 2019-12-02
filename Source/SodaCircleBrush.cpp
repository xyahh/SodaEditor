/*
  ==============================================================================

    SodaCircleBrush.cpp
    Created: 2 Dec 2019 6:50:00pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaBrush.h"


//Mid-Point Circle Drawing Algorithm.
//code source: https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/

void FSodaCircleBrush::startDraw(Image * image, const Point<float>& CurrentPixelUnderMouse)
{
	FSodaBrush::startDraw(image, CurrentPixelUnderMouse);
	originPoint = CurrentPixelUnderMouse;
}

void FSodaCircleBrush::updateDraw(Image * image, const Point<float>& CurrentPixelUnderMouse_)
{
	if (!FSodaBrush::preUpdateDraw(CurrentPixelUnderMouse_)) return;

	auto Vector = CurrentPixelUnderMouse_ - originPoint;

	float Dist = Vector.getDistanceFromOrigin();
	resetPixels(image);

	int x = Dist, y = 0;

	//(r, 0)
	drawPixel(image,
		+x + originPoint.x,
		originPoint.y
		, gProperties.brushSize, gProperties.brushColour);

	//if dist is 0, just draw the one pixel above^ and nothing else will be processed
	// these points are the points at the end of the X/Y axis direction from the center
	// of the circle
	if (Dist > 0)
	{
		//(-r, 0)
		drawPixel(image, 
			-x + originPoint.x,
			originPoint.y
			, gProperties.brushSize, gProperties.brushColour);

		//(0, r)
		drawPixel(image, 
			originPoint.x,
			+x + originPoint.y
			, gProperties.brushSize, gProperties.brushColour);

		//(0, -r)
		drawPixel(image, 
			originPoint.x,
			-x + originPoint.y,
			gProperties.brushSize, gProperties.brushColour);

	}

	int P = 1 - Dist;
	while (x > y)
	{
		++y;
		// Mid-point is inside or on the perimeter
		if (P <= 0)
			P = P + 2 * y + 1;
		// Mid-point is outside the perimeter
		else
		{
			--x;
			P = P + 2 * y - 2 * x + 1;
		}
		// All the perimeter points have already been printed
		if (x < y)
			break;

		// Drawing the generated point and its reflection
		// in the other octants after translation
		drawPixel(image, +x + originPoint.x, +y + originPoint.y
			, gProperties.brushSize, gProperties.brushColour);
		drawPixel(image, -x + originPoint.x, +y + originPoint.y
			, gProperties.brushSize, gProperties.brushColour);
		drawPixel(image, +x + originPoint.x, -y + originPoint.y
			, gProperties.brushSize, gProperties.brushColour);
		drawPixel(image, -x + originPoint.x, -y + originPoint.y
			, gProperties.brushSize, gProperties.brushColour);
		// If the generated point is on the line x = y then
		// the perimeter points have already been printed
		if (x != y)
		{
			drawPixel(image, +y + originPoint.x, +x + originPoint.y
				, gProperties.brushSize, gProperties.brushColour);
			drawPixel(image, -y + originPoint.x, +x + originPoint.y
				, gProperties.brushSize, gProperties.brushColour);
			drawPixel(image, +y + originPoint.x, -x + originPoint.y
				, gProperties.brushSize, gProperties.brushColour);
			drawPixel(image, -y + originPoint.x, -x + originPoint.y
				, gProperties.brushSize, gProperties.brushColour);
		}
	}


}
