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
#include "SodaGlobals.h"
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
	void update();

	// starts drawing whenever a mouse is clicked in the Canvas
	void startDraw(const MouseEvent& e);

	//updates mouse position whenever a mouse drag event is called in Canvas
	void updateMousePos(const MouseEvent& e);

	//drawing ends, isDrawing is set to false, and we move the pixel data to the caller.
	void endDraw(const MouseEvent& e, std::set<FPixel>* outPixels);

	// Converts a Position from the Component space (int) to the Image pixel space (float)
	Point<float> ConvertPosition(const Point<int>& Pos);

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

	int				layer_width;
	int				layer_height;
	int				layer_pixelSize;

	Point<int>		CurrentMousePosition;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaLayer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

