/*
  ==============================================================================

    SodaEraserBrush.cpp
    Created: 2 Dec 2019 9:50:51pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaBrush.h"

void FSodaEraserBrush::updateDraw(Image * image, const Point<float>& CurrentPixelUnderMouse)
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
	for (float i = 0.f; i <= Dist; i += 0.25f)
		drawPixel(image,
			PrevPixelUnderMouse.x + Vector.x * i, // X + dX
			PrevPixelUnderMouse.y + Vector.y * i, // Y + dY
			gProperties.brushSize, Colours::transparentBlack);
}
