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
class SodaRibbon  : public Component,
                    public FilenameComponentListener,
                    public Button::Listener,
                    public Slider::Listener
{
public:
    //==============================================================================
    SodaRibbon (SodaCanvas* canvas_);
    ~SodaRibbon();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* saveIcon_png;
    static const int saveIcon_pngSize;
    static const char* openIcon_png;
    static const int openIcon_pngSize;
    static const char* undoIcon_png;
    static const int undoIcon_pngSize;
    static const char* redoIcon_png;
    static const int redoIcon_pngSize;
    static const char* openIcon_png2;
    static const int openIcon_png2Size;
    static const char* undoIcon_png2;
    static const int undoIcon_png2Size;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SodaCanvas* canvas;

	FilenameComponent* fileLoader;
	FilenameComponent* fileSaver;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ImageButton> saveButton;
    std::unique_ptr<ImageButton> openButton;
    std::unique_ptr<ImageButton> undoButton;
    std::unique_ptr<ImageButton> redoButton;
    std::unique_ptr<Slider> pixelSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaRibbon)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

