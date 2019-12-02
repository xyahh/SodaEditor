/*
  ==============================================================================

    SodaBrush.h
    Created: 2 Dec 2019 6:49:39pm
    Author:  Juan

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SodaGlobals.h"

/* Parent Class for all the Brushes */
class FSodaBrush
{

public:

	FSodaBrush() {};
	virtual ~FSodaBrush() {};

	//starts the draw by clearing any possible pixels in the set, 
	// initializing the necessary variables and setting the 'isDrawing' flag to true
	virtual void startDraw(Image* i, const Point<float>& CurrentPixelUnderMouse);

	/*
	Where all the logic happens for different brushes.
	It records to two sets: 
	*/
	virtual void updateDraw(Image* i, const Point<float>& CurrentPixelUnderMouse) = 0;

	//checks whether we can proceed with the draw update or not
	// if the mouse hasn't moved, then it returns false
	// or if the drawing has ended (i.e. isDrawing == false), it also returns false
	bool preUpdateDraw(const Point<float>& CurrentPixelUnderMouse);
	
	// ends the draws, commits the Pixels to the outPixel pointer (by moving the data)
	//sets the 'isDrawing' flag to false
	void endDraw(Image* i, std::set<FPixel>* outPixels);

protected:

	/*
	Resets the pixels as if Nothing had been drawn.
	This is like an 'undo' of the drawing
	*/
	void resetPixels(Image* i);

	// draws into a Pixel with a given color and possibly neighboring ones depending on the brushsize.
	void drawPixel(Image* i, int X, int Y, int brushSize, const Colour& colour);
	
protected:
	Point<float> PixelUnderMouse;
	bool		 isDrawing;
	
private:
	std::set<FPixel> Pixels;
};

/*
Free Style Soda Brush
@ Draw freely. 
*/
class FSodaFreeStyleBrush : public FSodaBrush
{
public:
	FSodaFreeStyleBrush() {}

	virtual ~FSodaFreeStyleBrush() {}

	virtual void updateDraw(Image* i, const Point<float>& CurrentPixelUnderMouse);

};

/*
Circle Style Soda Brush
@ Draws a Circle with no Fill (just Border)
@ The Circle radius depends om the distance between the 
initial Mouse DOWN cursor position and the MOUSE UP cursor position. 
*/
class FSodaCircleBrush : public FSodaBrush
{
public:
	FSodaCircleBrush() {}

	virtual ~FSodaCircleBrush() {}

	virtual void startDraw(Image* i, const Point<float>& CurrentPixelUnderMouse);

	virtual void updateDraw(Image* i, const Point<float>&CurrentPixelUnderMouse);


private:

	Point<float> originPoint;

};


extern FSodaFreeStyleBrush	FreeStyleBrush;
extern FSodaCircleBrush		CircleBrush;