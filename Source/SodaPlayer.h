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
class SodaPlayer  : public Component,
                    public Button::Listener
{
public:
    //==============================================================================
    SodaPlayer (SodaCanvas* canvas_);
    ~SodaPlayer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

    // Binary resources:
    static const char* playIcon_png;
    static const int playIcon_pngSize;
    static const char* reverseIcon_png;
    static const int reverseIcon_pngSize;
    static const char* playIcon_png2;
    static const int playIcon_png2Size;
    static const char* pauseIcon_png;
    static const int pauseIcon_pngSize;
    static const char* reverseIcon_png2;
    static const int reverseIcon_png2Size;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SodaCanvas* sodaCanvas;
	bool		isReversed;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ImageButton> playButton;
    std::unique_ptr<ImageButton> reverseButton;
    std::unique_ptr<ImageButton> pauseButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaPlayer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

