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
#include "Delegate.h"
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

	/*
	@ Creates a Layer and sets it as Active.
	@ it creates a map between the ID specified and the index the layer is at.
	@ it also pushes the layer creation command into the undo stack.
	@ returns true if the operations were successful or false if the ID already exists in the map
	*/
	bool createLayer(size_t id);

	/*
	@ Deletes the designated layer. If it was the active layer, the program will look
	for the next active layer and set it as Active.
	@ It also pushes the layer deletion command, which contains a copy of what was deleted, into
	the undo stack.
	*/
	bool deleteLayer(size_t id);

	/*
	@ Swaps a Subject/Target layer with another Layer
	*/
	bool swapLayers(size_t targetLayer, size_t otherLayer);

	/*
	@ Adds settings to the Playback
	@ i.e. performs bitwise operator |= value
	@ These settings are found in the ESodaPlayback enum
	*/
	void addPlaybackSettings(int Settings);

	/*
	@ Removes settings from the Playback
	@ i.e. performs bitwise operator &= ~value
	@ These settings are found in the ESodaPlayback enum
	*/
	void removePlaybackSettings(int Settings);

	/*
	@ Sets the FPS of the Playback
	*/
	void setPlaybackFPS(int FPS);

	/* Sets Active Layer by first Deactivating the Currently active one and then
	activating the new one
	@ returns true if the id was found and the index mapped was in range & was activated. false if out of range or id not found
	*/
	bool setActiveLayer(size_t id);

	/* Sets Active Layer by first Deactivating the Currently active one and then
	activating the new one
	@ returns true if the index was in range & was activated. false if index out of range
	*/
	bool setActiveLayerIndex_Internal(size_t index);


	/* Gets the Current Active Layer ID
	*/
	void getActiveLayerID(size_t* id) const;

	/*
	checks whether a given id is the active layer
	@ true if the id is the active layer
	@ false otherwise
	*/
	bool isActiveLayer(size_t id) const;

	/*
	Tries to find the index mapped to the layer id.
	if found, will return true and will fill the data
	if not found, will return false.
	*/
	bool findLayerIndex(size_t id, size_t* outIndex) const;

	/*
	Gets current Active Layer as a pointer
	@ returns true if
	*/
	bool getLayer(size_t id, SodaLayer** outLayer);

	void resizeLayer(SodaLayer& layer);
	/*
	Pushes a NEW command into the Undo Stack and
	deletes all the commands from the redo stack as we are writing
	a new timeline of commands

	@returns true if successful. returns the Execute result if ExecuteFlag is true
	@ returns false if Execute result is false or if command is invalid
	*/
	bool registerNewCommand(FSodaCommand* command, bool execute);
	bool undo();
	bool redo();


	/*
	Internal creation of layer (should only be used by Commands)
	if image source is specified, it copies the contents of source
	into the new layer
	*/
	bool createLayer_Internal(size_t id, Image* source);

	/*
	Internal deletion of layer (should only be used by Commands)
	if copy is specified, it copies the contents of the layer into copy
	*/
	bool deleteLayer_Internal(size_t id, Image* copy);

	/*
	Internal func to set an Active Layer with the given id.
	returns false if no id was found. 
	returns true if operation was successful
	*/
	bool setActiveLayer_Internal(size_t id);

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

public:

	/*
	@ Delegate that fires when a Layer has been created.
	@ @param 1 size_t: the Layer ID of the layer created.
	*/
	FDelegate<size_t> OnLayerCreated;

	/*
	@ Delegate that fires when a Layer has been destroyed.
	@ @param 1 size_t: the Layer ID of the layer destroyed.
	*/
	FDelegate<size_t> OnLayerDestroyed;

private:

	/*
	A deque of Layers drawn in order.
	Layers are drawn from Begin to End
	i.e. a layer with a higher index will be drawn over
	a layer with lower index
	*/
	std::deque<SodaLayer*> layers;

	/*
	A map that maps one given ID to the actual index
	of that ID in the layer deque. This is to manage the
	movement of the layers from within the canvas and not invalidate/update
	the indices/ids of layers from other components
	*/
	std::map<size_t, size_t> layerIDmap;

	/*
	Indicator of the Id of the currently Active Layer.
	*/
	size_t activeLayerId;

	/*
	Indicator of the Index of the currently Active Layer.
	When drawing, on the Screen, it will only draw in the
	Active Layer.
	*/
	size_t activeLayer;

	/*
	the current Resolution of the Canvas
	*/
	int resolution;

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


	int canvasUpdateFPS;

	int updateFramesPassed;
	int playbackFPS;


	/*
	Informs the type of Playback currently occurring.
	Whether it is playing or it's stopped, or what other actions can be performed on the
	deque of layers.
	*/
	int playbackSettings;

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

