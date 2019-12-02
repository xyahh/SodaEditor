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
	{}
	
	Colour brushColour;
	int brushSize;
	Image* image;
	FSodaBrush* brush;
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

