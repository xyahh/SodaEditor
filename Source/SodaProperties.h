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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SodaProperties  : public Component,
                        public ChangeListener,
                        public Button::Listener,
                        public Slider::Listener
{
public:
    //==============================================================================
    SodaProperties (SodaCanvas* canvas_);
    ~SodaProperties();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	/* Callback func to catch any  ChangeBroadcaster we are listening to */
	void changeListenerCallback(ChangeBroadcaster* source) override;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> brushGroup;
    std::unique_ptr<TextButton> paletteButton;
    std::unique_ptr<GroupComponent> layerGroup;
    std::unique_ptr<Slider> brushSlider;
    std::unique_ptr<Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaProperties)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

