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
//[/Headers]

#include "SodaCanvas.h"
#include "SodaRibbon.h"
#include "SodaToolbox.h"
#include "SodaPlayer.h"
#include "SodaProperties.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SodaWindow  : public Component
{
public:
    //==============================================================================
    SodaWindow ();
    ~SodaWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;

    // Binary resources:
    static const char* saveIcon_png;
    static const int saveIcon_pngSize;
    static const char* openIcon_png;
    static const int openIcon_pngSize;
    static const char* openIcon_png2;
    static const int openIcon_png2Size;
    static const char* undoIcon_png;
    static const int undoIcon_pngSize;
    static const char* redoIcon_png;
    static const int redoIcon_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<SodaCanvas> sodaCanvas;
    std::unique_ptr<SodaRibbon> ribbonComponent;
    std::unique_ptr<SodaToolbox> toolBoxComponent;
    std::unique_ptr<SodaPlayer> playerComponent;
    std::unique_ptr<SodaProperties> propertiesComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SodaWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

