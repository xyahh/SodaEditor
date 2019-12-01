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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SodaToolbox.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "SodaGlobals.h"
//[/MiscUserDefs]

//==============================================================================
SodaToolbox::SodaToolbox (SodaCanvas* canvas_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    imagePreview.reset (new GroupComponent ("imagePreview",
                                            TRANS("Preview")));
    addAndMakeVisible (imagePreview.get());

    groupComponent.reset (new GroupComponent ("new group",
                                              TRANS("Layers")));
    addAndMakeVisible (groupComponent.get());


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	setFramesPerSecond(30);
    //[/Constructor]
}

SodaToolbox::~SodaToolbox()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    imagePreview = nullptr;
    groupComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SodaToolbox::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    //[UserPaint] Add your own custom painting code here..

	//draw if there's an image available
	if (gCurrentProperties.currentImage)
	{
		g.setImageResamplingQuality(Graphics::ResamplingQuality::lowResamplingQuality);
		g.drawImage(*gCurrentProperties.currentImage, previewRectangle, RectanglePlacement::centred);
	}


    //[/UserPaint]
}

void SodaToolbox::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    imagePreview->setBounds (0, 0, proportionOfWidth (1.0000f), 256);
    groupComponent->setBounds (0, 266, proportionOfWidth (1.0000f), getHeight() - 275);
    //[UserResized] Add your own custom resize handling here..
	auto imagePreviewRect = imagePreview->getBounds().toFloat();

	previewRectangle = imagePreviewRect * 0.9f;
	previewRectangle.setLeft(imagePreviewRect.getWidth() * 0.1f);
	previewRectangle.setTop(imagePreviewRect.getHeight() * 0.1f);
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SodaToolbox" componentName=""
                 parentClasses="public AnimatedAppComponent" constructorParams="SodaCanvas* canvas_"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff808080"/>
  <GROUPCOMPONENT name="imagePreview" id="8b984c2d2be3b733" memberName="imagePreview"
                  virtualName="" explicitFocusOrder="0" pos="0 0 100% 256" title="Preview"/>
  <GROUPCOMPONENT name="new group" id="fdc7952107ea4195" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 266 100% 275M" title="Layers"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

