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
@ Soda Playback Enum Class
@ Used to identify the current playback
*/
enum ESodaPlayback
{
	Playback_Playing	= 0x1,
	Playback_Reversed	= 0x2,
};

class FSodaBrush;

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
		, image(nullptr)
		, brush(nullptr)
		, isGridVisible(true)
		, pixelSize(10)
	{}
	
	Colour brushColour;

	int brushSize;

	/*
	Pointer to the Current Image being drawn.
	This is the image that the SodaLayer class wraps around.
	*/
	Image* image;


	/*
	Pointer to the Current brush.
	This allows us to make even more types of brush without editing anything.
	*/
	FSodaBrush* brush;

	/*
	the Size of the Pixels of the Canvas that is drawn into the Window.
	We can think of it as the 'Zoom' of the Canvas
	or ratio of the real pixels to the Sprite Pixel
	*/
	int pixelSize;

	/* 
	Flag whether to draw the Grid or not (true to draw)
	*/
	bool isGridVisible;
};

extern FSodaProperties gProperties;

struct FPixel
{
	FPixel(int x_, int y_, const Colour& newColour_, const Colour& oldColour_) 
		: x(x_)
		, y(y_)
		, newColour(newColour_)
		, oldColour(oldColour_)
	{}

	bool operator<(const FPixel& other) const
	{
		if (x != other.x) return x < other.x;
		else return y < other.y;
	}

	int x;
	int y;
	Colour newColour;
	Colour oldColour;
};

