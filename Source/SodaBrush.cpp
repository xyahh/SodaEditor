/*
  ==============================================================================

    SodaBrush.cpp
    Created: 2 Dec 2019 6:49:39pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaBrush.h"
#include "SodaCommand.h"

//Extern Brushes initialized here 
FSodaFreeBrush		SodaFreeBrush;
FSodaCircleBrush	SodaCircleBrush;
FSodaLineBrush		SodaLineBrush;
FSodaRectBrush		SodaRectBrush;
FSodaEraserBrush	SodaEraserBrush;

void FSodaBrush::resetPixels(Image* image)
{
	FSodaDrawCommand drawCommand(image, std::move(Pixels));
	drawCommand.undo(nullptr); //canvas can be nullptr here since we only deal with Image
}

void FSodaBrush::startDraw(Image * image, const Point<float>& CurrentPixelUnderMouse)
{
	//clear the Pixels
	Pixels.clear();

	//asign point to latest coordinates
	PixelUnderMouse = CurrentPixelUnderMouse;

	//star drawing
	isDrawing = true;
}

bool FSodaBrush::preUpdateDraw(const Point<float>& CurrentPixelUnderMouse)
{
	//if nothing has changed or we do not have permision to draw, return false
	if (PixelUnderMouse == CurrentPixelUnderMouse || !isDrawing) return false;
	//updates the latest mouse pos pixel if there's any change, and returns true;
	PixelUnderMouse = CurrentPixelUnderMouse;
	return true;
}

void FSodaBrush::endDraw(Image* image, std::set<FPixel>* outPixels)
 {
	//set drawing to false and commit the pixels to *outPixels
	isDrawing = false;
	*outPixels = std::move(Pixels);
	// reset the Pixels by undoing any possible overdraw (this shouldn't happen, though)
	resetPixels(image);
 }

 void FSodaBrush::drawPixel(Image * image, int X, int Y, int brushSize, const Colour & colour)
 {


	 // we check by going vertically and filling each row by 
	 // a certain amount.We know that the highest/lowest row will be 1
	 // the second highest/lowest, will be 3...
	 // row 0 (where row = Y) is the BrushSize*2 - 1. So for BrushSize = 3; the size of the row 0 will be 5 
	 int rangeY = (brushSize - 1);
	 for (int dy = -rangeY; dy <= rangeY; ++dy)
	 {
		 //range X is calculated by the sequence mentioned above
		 // since we're checking both sides, by doing -rangeX and rangeX,
		 //we divide rangeX by 2
		 int rangeX = (2 * (brushSize - abs(dy)) - 1) / 2;
		 for (int dx = -rangeX; dx <= rangeX; ++dx)
		 {
			 int px = X + dx;
			 int py = Y + dy;
			 //save the oldColour before setting the pixel so that we can empalce the correct original colour
			 Colour oldColour = image->getPixelAt(px, py);
			 image->setPixelAt(px, py, colour);
			 Pixels.emplace(px, py, colour, oldColour);
		 }
	 }
 }