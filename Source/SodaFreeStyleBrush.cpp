/*
  ==============================================================================

    SodaFreeStyleBrush.cpp
    Created: 2 Dec 2019 6:49:54pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaBrush.h"

void FSodaFreeStyleBrush::updateDraw(Image * i, const Point<float>& CurrentPixelUnderMouse)
{
	//save current PixelUndermouse to a variable so that we can know the prev value after it changes 
	// in the preupdate
	auto PrevPixelUnderMouse = PixelUnderMouse;

	if (!FSodaBrush::preUpdateDraw(CurrentPixelUnderMouse)) return;

	//Getting vector from prev->Curr and obtaining normalized direction
	auto Vector = CurrentPixelUnderMouse - PrevPixelUnderMouse;
	float Dist = Vector.getDistanceFromOrigin();
	Vector /= Dist;

	//drawing all the pixels that come in the path of this vector from prev->Curr
	for (float f = 0.f; f <= Dist; f += 0.25f)
		drawPixel(i,
			PrevPixelUnderMouse.x + Vector.x * f, // X + dX
			PrevPixelUnderMouse.y + Vector.y * f, // Y + dY
			gProperties.brushSize, gProperties.brushColour);
}
