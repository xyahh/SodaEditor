/*
  ==============================================================================

    SodaCommand.h
    Created: 2 Dec 2019 8:38:30pm
    Author:  Juan

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SodaGlobals.h"

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
	virtual bool isValid() const = 0;
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

	FSodaDrawCommand(Image* imageToDrawOn, std::set<FPixel>&& Pixels_)
		: image(imageToDrawOn)
		, Pixels(std::move(Pixels_))
	{
	}

	virtual bool execute(SodaCanvas* canvas)
	{
		if (!image) return false;
		//set the new color of the pixel
		for (auto& pixel : Pixels)
			image->setPixelAt(pixel.x, pixel.y, pixel.newColour);
		return true;
	}

	virtual bool undo(SodaCanvas* canvas)
	{
		if (!image) return false;
		//set the colour of the pixel to the previous color
		for (auto& pixel : Pixels)
			image->setPixelAt(pixel.x, pixel.y, pixel.oldColour);
		return true;
	}

	//if there's no new pixels to add, then we don't do anything
	virtual bool isValid() const override
	{
		return !Pixels.empty() && image;
	}

private:
	Image* image;
	std::set<FPixel> Pixels;
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

	virtual bool isValid()
	{
		return true;
	}

private:
	size_t layerToActivate;
	size_t prevActiveLayer;
	bool prevActiveLayerValid;
};

/*

*/
class FSodaCreateLayerCommand : public FSodaCommand
{
public:
	FSodaCreateLayerCommand(size_t id_) : id(id_) {}

	virtual bool execute(SodaCanvas* canvas);
	virtual bool undo(SodaCanvas* canvas);

	virtual bool isValid() const override
	{
		return true;
	}

private:
	size_t id;
};

/*
This command was separated from the CreateLayer command because we do
care what was deleted! It must be stored somewhere so here is where we stoered what we deleted
*/
class FSodaDeleteLayerCommand : public FSodaCommand
{
public:

	FSodaDeleteLayerCommand(size_t id_) : id(id_) {}
	virtual ~FSodaDeleteLayerCommand() {}

	virtual bool execute(SodaCanvas* canvas);
	virtual bool undo(SodaCanvas* canvas);

	virtual bool isValid() const override
	{
		return true;
	}

private:
	size_t id;
	Image  image;
};