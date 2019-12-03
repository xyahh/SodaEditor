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
#include "SodaCanvas.h"
#include "SodaLayerBoxList.h"
#include <map>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SodaToolbox  : public AnimatedAppComponent,
                     public Button::Listener
{
public:
    //==============================================================================
    SodaToolbox (SodaCanvas* canvas_);
    ~SodaToolbox();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void update() override;

	void createLayer();
	void layerCreated(size_t layer_id);
	void layerDestroyed(size_t layer_id);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	SodaCanvas*		sodaCanvas;

	Rectangle<float> previewRectangle;

	LayerListBoxItemData itemData;
	LayerListBoxModel listBoxModel;
	DraggableListBox  listBox;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> imagePreview;
    std::unique_ptr<GroupComponent> layerGroup;
    std::unique_ptr<TextButton> createLayerButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaToolbox)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

