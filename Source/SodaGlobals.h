/*
  ==============================================================================

    SodaGlobals.h
    Created: 30 Nov 2019 9:26:49pm
    Author:  Juan

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <set>

/*
Enum class that tells us 
what type of Shape we are currently drawing/selected

@ FreeStyle: Free drawing, no algorithms used. Just color the pixels that the mouse passes through
@ Circle: Circle that increases in radius as the Mouse moves away from the origin point
@ Rectangle: Rect that increases in size as the mouse moves away from the origin point

*/
enum class ESodaShapes
{
	FreeStyle,
	Circle,
	Rectangle
};


/* Soda Properties
@ Used to keep control of properties like
BRUSH settings (Colour, size, etc)
GridVisibility (should we draw the Grid)
*/
struct FSodaProperties
{
	FSodaProperties()
		: brushColour(Colours::white)
		, brushSize(1) 
		, currentImage(nullptr)
		, isGridVisible(true)
		, currentBrush(ESodaShapes::FreeStyle)
	{}
	
	Colour brushColour;
	int brushSize;
	Image* currentImage;
	bool isGridVisible;
	ESodaShapes currentBrush;
};

extern FSodaProperties gCurrentProperties;

struct FPixel
{
	FPixel(int x_, int y_, const Colour& colour_) 
		: x(x_)
		, y(y_)
		, colour(colour_)
	{}

	bool operator<(const FPixel& other) const
	{
		if (x != other.x) return x < other.x;
		else return y < other.y;
	}

	int x;
	int y;
	Colour colour;
};

class SodaCanvas;

/*

----------------------------------------------------------------------------------
SODA COMMANDS
----------------------------------------------------------------------------------

@ used to keep track of what commands we have executed!

@ Call execute when we want to execute/redo
@ Call redo func when redoing

@ Each func returns a bool. If true is returned,
these functions executed successfully. If false, then something was
wrong with the info given (e.g. a nullptr image).
*/

//Parent class. Does nothing
class FSodaCommand
{
public:
	FSodaCommand() {}
	virtual ~FSodaCommand() {}

	/*
	@ Executes the Command assigned.
	This is also used as the 'redo' func
	@returns true if the execute went as expected.
	*/
	virtual bool execute(SodaCanvas* canvas) = 0;
	/*
	@ this func does the opposite that execute does
	@ and undos all the things execute did
	@returns true if the execute went as expected
	*/
	virtual bool undo(SodaCanvas* canvas) = 0;


	/*
	this func check whethers this command can be executed/undone
	or has any meaning at all.
	(e.g. executing a command on a deleted image would return false);
	*/
	virtual bool isValid() = 0;
};

/*
Command that Draws on a list of Pixels with colours
@ This can be optimized by having a deque of X, Y in "newPixels" and have 
1 instance of Colour outside. However, this is only if we assume that the brush
we use is 1-colour. 
@ we will need a different Struct for this.
*/
class FSodaDrawCommand : public FSodaCommand
{
public:

	FSodaDrawCommand(Image* imageToDrawOn, std::set<FPixel>&& newPixels_, std::set<FPixel>&& oldPixels_)
		: image(imageToDrawOn)
		, newPixels(std::move(newPixels_))
		, oldPixels(std::move(oldPixels_))
	{
	}

	virtual bool execute(SodaCanvas* canvas)
	{
		if (!image) return false;

		for (auto& newPixel : newPixels)
		{
			//retrieve previous color of pixel before we color on it
			//oldPixels.emplace(newPixel.x, newPixel.y, image->getPixelAt(newPixel.x, newPixel.y));
			//set the new color of the pixel
			image->setPixelAt(newPixel.x, newPixel.y, newPixel.colour);
		}
		return true;
	}

	virtual bool undo(SodaCanvas* canvas)
	{
		if (!image) return false;
		//set the colour of the pixel to the previous color
		for (auto& oldPixel : oldPixels)
		{
			image->setPixelAt(oldPixel.x, oldPixel.y, oldPixel.colour);
		}
		//once we finish we clear the oldPixels struct since we will  emplace them back when we execute the command again 
		//oldPixels.clear();
		return true;
	}

	//if there's no new pixels to add, then we don't do anything
	virtual bool isValid() override
	{
		return !newPixels.empty() && image;
	}

private:

	Image* image;

	std::set<FPixel> newPixels;
	std::set<FPixel> oldPixels;
};

/*
Command that Activates 1 layer
*/
class FSodaActivateLayerCommand
{
public:

	FSodaActivateLayerCommand(size_t layerToActivate_)
		: layerToActivate(layerToActivate_) {}

	//moved these functionalities to CPP because we need SodaCanvas functionality
	virtual bool execute(SodaCanvas* canvas);
	virtual bool undo(SodaCanvas* canvas);
	

private:
	size_t layerToActivate;
	size_t prevActiveLayer;
	bool prevActiveLayerValid;
};

/*

*/
class FSodaCreateLayerCommand
{

};

/*
This command was separated from the CreateLayer command because we do
care what was deleted! It must be stored somewhere so here is where we stoered what we deleted
*/
class FSodaDeleteLayerCommand
{

};