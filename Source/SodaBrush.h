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
	virtual void startDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);

	/*
	Where all the logic happens for different brushes.
	It records to two sets: 
	*/
	virtual void updateDraw(Image* image, const Point<float>& CurrentPixelUnderMouse) = 0;

	//checks whether we can proceed with the draw update or not
	// if the mouse hasn't moved, then it returns false
	// or if the drawing has ended (i.e. isDrawing == false), it also returns false
	bool preUpdateDraw(const Point<float>& CurrentPixelUnderMouse);
	
	// ends the draws, commits the Pixels to the outPixel pointer (by moving the data)
	//sets the 'isDrawing' flag to false
	void endDraw(Image* image, std::set<FPixel>* outPixels);

protected:

	/*
	Resets the pixels as if Nothing had been drawn.
	This is like an 'undo' of the drawing
	*/
	void resetPixels(Image* image);

	// draws into a Pixel with a given color and possibly neighboring ones depending on the brushsize.
	void drawPixel(Image* image, int X, int Y, int brushSize, const Colour& colour);
	
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
class FSodaFreeBrush : public FSodaBrush
{
public:
	FSodaFreeBrush() {}

	virtual ~FSodaFreeBrush() {}

	virtual void updateDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);

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

	virtual void startDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);

	virtual void updateDraw(Image* image, const Point<float>&CurrentPixelUnderMouse);


private:

	Point<float> originPoint;

};

/*
Line Style Soda Brush
@ Draws a Straight Line from the moment the Mouse was Down (Origin)
@ to the moment it is lifted mouse up (Destination)
*/
class FSodaLineBrush : public FSodaBrush
{
public:

	FSodaLineBrush() {}
	virtual ~FSodaLineBrush() {}

	virtual void startDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);

	virtual void updateDraw(Image* image, const Point<float>&CurrentPixelUnderMouse);

private:

	Point<float> originPoint;
};


/*
Rect Style Soda Brush
@ Draws a Rect with no Fill (just Border)
@ The Rect size(x,y) depends on the distance between the
initial Mouse DOWN cursor position and the MOUSE UP cursor position.
*/
class FSodaRectBrush : public FSodaBrush
{
public:
	FSodaRectBrush() {}

	virtual ~FSodaRectBrush() {}

	virtual void startDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);

	virtual void updateDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);


private:

	Point<float> originPoint;

};

/*
Eraser Style Soda Brush
@ Is Exactly the same as FreeLine brush
@ except that the Colour is TransparentBlack(i.e. 0.f, 0.f, 0.f, 0.f)
@ instead of the Colour set in the Palette
*/
class FSodaEraserBrush : public FSodaBrush
{
public:
	FSodaEraserBrush() {}

	virtual ~FSodaEraserBrush() {}

	virtual void startDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);

	virtual void updateDraw(Image* image, const Point<float>& CurrentPixelUnderMouse);
};

//Brush Types (Global)
extern FSodaFreeBrush		SodaFreeBrush;
extern FSodaCircleBrush		SodaCircleBrush;
extern FSodaLineBrush		SodaLineBrush;
extern FSodaRectBrush		SodaRectBrush;
extern FSodaEraserBrush		SodaEraserBrush;