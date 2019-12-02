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
#include "SodaCommand.h"
#include "SodaLayer.h"
#include <deque>
#include <stack>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SodaCanvas  : public AnimatedAppComponent
{
public:
    //==============================================================================
    SodaCanvas ();
    ~SodaCanvas();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	virtual void update();

	/* Sets Active Layer by first Deactivating the Currently active one and then
	activating the new one
	@ returns true if the index was in range & was activated. false if out of range
	*/
	bool setActiveLayer(size_t index);

	/* Gets the Current Active Layer
	@ returns true if the index was in range and is a valid active layer. false if out of range
	*/
	bool getActiveLayer(size_t* outIndex) const;

	void registerNewCommand(FSodaCommand* command, bool execute);
	bool undo();
	bool redo();

	/* Saves the Canvas to file
	@param filename: The destination of the image(s). if it's more
	than one image, each image will be named with a number appended
	(i.e. filename_1, filename_2, filename_3...)
	@layerPerFile: if to save  1 layer per file or to save all of the
	layers in one single grid.
	*/
	void saveCanvasToFile(const String& filename, bool layerPerFile);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    bool keyPressed (const KeyPress& key) override;

    // Binary resources:
    static const char* icon_png;
    static const int icon_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	/*
	A list of Layers drawn in order.
	Layers are drawn from Begin to End
	i.e. a layer with a higher index will be drawn over
	a layer with lower index
	*/
	std::deque<SodaLayer> layers;


	/*
	Indicator of the Index of the currently Active Layer.
	When drawing, on the Screen, it will only draw in the
	Active Layer.
	*/
	size_t activeLayer;

	/*
	the Size of the Pixels of the Canvas that is drawn into the Window.
	We can think of it as the 'Zoom' of the Canvas
	or ratio of the real pixels to the Sprite Pixel
	*/
	int pixelSize;

	/*
	The bounds defined by the layer. Used to draw the grid
	*/
	Rectangle<int> layerBounds;

	/*
	Two Stacks representing what has been Undone and redone.
	If we call UNDO:
	1) the last added action is popped and "undo" func is called.
	2) This popped command is pushed into the redo stack.

	If we call REDO:
	1) the last added command is popped and "execute" func is called (like we are doing the action once again)
	2) this command is pushed into the undo stack.

	If a new Command is triggered:
	1) It is executed and then pushed into the Undo stack.
	2) the Redo Stack is cleared (since it's not logical to pop a redo of an old command and put it ontop of this new command)
	*/
	std::stack<FSodaCommand*> undoStack;
	std::stack<FSodaCommand*> redoStack;


	float timerFrequency;
	/*
	Keys to check for in Update func
	*/
	KeyPress undoKey;
	KeyPress redoKey;
	bool commandDown;

	/*
	How frequent to call the KeyPresses. if current timer is greater than
	the currentMultiple, then we go ahead and process they key and
	divide the currentMultiple by some amount.
	The currentMultiple becomes smaller and so these actions become more frequent as we go!
	Clamp at a lowMultiple;
	*/
	float	currentTimer;
	float	currentMultiple;
	float	lowestMultiple;
	float	initialMultiple;

	/*
	bool to inform whether we are currently drawing/erasing to the screen
	*/
	bool isDrawing;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaCanvas)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

