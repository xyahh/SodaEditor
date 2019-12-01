/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"

class FSodaDrawCommand;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
 Soda Layer

 @ Is the class that Describes & Updates the contents of the image we are drawing to.
 @ It is also in charge of processing Mouse events and mapping it to the Image range

                                                                    //[/Comments]
*/
class SodaLayer  : public Component
{
public:
    //==============================================================================
    SodaLayer (int width_, int height_, int pixelSize_);
    ~SodaLayer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	// updates 60hz
	void update(FSodaDrawCommand* drawCommand);

	// updates the mouse position whenever a mouse event is called in the Canvas
	void draw(const MouseEvent& e, FSodaDrawCommand* drawCommand);
	void drawAt(int X, int Y, int brushSize, const Colour& colour, FSodaDrawCommand* drawCommand);
	// Converts a Position from the Component space to the Image pixel space
	Point<int> ConvertPosition(const Point<int>& Pos);
	Image* getLayerImage();

	void onActivation();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	/*
	@ Image that represents the Layer we are drawing to.
	*/
	Image			image;

	/* Record the the Current & Previous Mouse Coordinates so that we can detect
	*  if there were missing squares in between these two mouse positions
	*/
	Point<int>		PreviousMouseCoords;
	Point<int>		CurrentMouseCoords;

	int				layer_width;
	int				layer_height;
	int				layer_pixelSize;

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaLayer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

