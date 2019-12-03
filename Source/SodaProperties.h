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

    // Binary resources:
    static const char* freeDrawIcon_png;
    static const int freeDrawIcon_pngSize;
    static const char* circleIcon_png;
    static const int circleIcon_pngSize;
    static const char* lineIcon_png;
    static const int lineIcon_pngSize;
    static const char* rectIcon_png;
    static const int rectIcon_pngSize;
    static const char* eraserIcon_png;
    static const int eraserIcon_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SodaCanvas* sodaCanvas;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> canvasGroup;
    std::unique_ptr<GroupComponent> brushGroup;
    std::unique_ptr<GroupComponent> brushTypeGroup;
    std::unique_ptr<TextButton> paletteButton;
    std::unique_ptr<Label> label;
    std::unique_ptr<ImageButton> freeStyle;
    std::unique_ptr<ImageButton> circleStyle;
    std::unique_ptr<ImageButton> lineStyle;
    std::unique_ptr<ImageButton> rectStyle;
    std::unique_ptr<ImageButton> eraserStyle;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Slider> brushSlider;
    std::unique_ptr<Slider> pixelScaleSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaProperties)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

