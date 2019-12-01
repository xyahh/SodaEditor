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

#include "SodaProperties.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "SodaGlobals.h"
//[/MiscUserDefs]

//==============================================================================
SodaProperties::SodaProperties (SodaCanvas* canvas_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    brushGroup.reset (new GroupComponent ("brushGroup",
                                          TRANS("Brush")));
    addAndMakeVisible (brushGroup.get());
    brushGroup->setTextLabelPosition (Justification::centredLeft);

    paletteButton.reset (new TextButton ("paletteButton"));
    addAndMakeVisible (paletteButton.get());
    paletteButton->setButtonText (TRANS("Palette"));
    paletteButton->addListener (this);

    layerGroup.reset (new GroupComponent ("layerGroup",
                                          TRANS("Image")));
    addAndMakeVisible (layerGroup.get());
    layerGroup->setTextLabelPosition (Justification::centredLeft);

    brushSlider.reset (new Slider ("brushSlider"));
    addAndMakeVisible (brushSlider.get());
    brushSlider->setRange (1, 4, 1);
    brushSlider->setSliderStyle (Slider::LinearVertical);
    brushSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    brushSlider->addListener (this);

    label.reset (new Label ("new label",
                            TRANS("Brush\n"
                            "Size")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 1000);


    //[Constructor] You can add your own custom stuff here..

	//Set as Default starting Colour
	gCurrentProperties.brushColour = Colours::black;
	gCurrentProperties.brushSize = 1;
    //[/Constructor]
}

SodaProperties::~SodaProperties()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    brushGroup = nullptr;
    paletteButton = nullptr;
    layerGroup = nullptr;
    brushSlider = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SodaProperties::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SodaProperties::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    brushGroup->setBounds (0, 0, proportionOfWidth (1.0000f), 250);
    paletteButton->setBounds (0 + proportionOfWidth (1.0000f) / 2 + -1 - ((roundToInt (proportionOfWidth (1.0000f) * 0.7500f)) / 2), 30, roundToInt (proportionOfWidth (1.0000f) * 0.7500f), 24);
    layerGroup->setBounds (0, 250, proportionOfWidth (1.0000f), 250);
    brushSlider->setBounds (0 + proportionOfWidth (1.0000f) / 2 + -1 - ((roundToInt (proportionOfWidth (1.0000f) * 0.7500f)) / 2), 0 + 75, roundToInt (proportionOfWidth (1.0000f) * 0.7500f), 150);
    label->setBounds ((0 + proportionOfWidth (1.0000f) / 2 + -1 - ((roundToInt (proportionOfWidth (1.0000f) * 0.7500f)) / 2)) + 0, (0 + 75) + 20, 150, 50);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SodaProperties::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == paletteButton.get())
    {
        //[UserButtonCode_paletteButton] -- add your button handler code here..

		/*
		* a new palette is created everytime we click on this
		*/
		auto* colourSelector = new ColourSelector();
		colourSelector->setName("ColourSelector");

		/*
		* make the current default color the selected brush color, which is the color of the
		* palette button
		*/
		colourSelector->setCurrentColour(paletteButton->findColour(TextButton::buttonColourId));

		/*
		* Listening to every Colour change on this
		*/
		colourSelector->addChangeListener(this);

		colourSelector->setColour(ColourSelector::backgroundColourId, Colours::transparentBlack);
		colourSelector->setSize(300, 400);

		/*
		* Launch the colourSelector async & next to the paletteButton
		*/
		CallOutBox::launchAsynchronously(colourSelector, paletteButton->getScreenBounds() , nullptr);

        //[/UserButtonCode_paletteButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SodaProperties::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == brushSlider.get())
    {
        //[UserSliderCode_brushSlider] -- add your slider handling code here..
		gCurrentProperties.brushSize = static_cast<int>(brushSlider->getValue());
        //[/UserSliderCode_brushSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void SodaProperties::changeListenerCallback(ChangeBroadcaster * source)
{
	//if what we are listening to is a Colour Selector, then that means colour has changed and we
	// update the paletteButton's colour to the current selected colour of the ColourSelector
	if (auto* cs = dynamic_cast<ColourSelector*>(source))
	{
		Colour colour = cs->getCurrentColour();
		paletteButton->setColour(TextButton::buttonColourId, colour);
		gCurrentProperties.brushColour = colour;
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SodaProperties" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="SodaCanvas* canvas_"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="1000">
  <BACKGROUND backgroundColour="ff808080"/>
  <GROUPCOMPONENT name="brushGroup" id="2c65e22a40bc686b" memberName="brushGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 0 100% 250" title="Brush"
                  textpos="33"/>
  <TEXTBUTTON name="paletteButton" id="2e78eaf6e5c8fc8a" memberName="paletteButton"
              virtualName="" explicitFocusOrder="0" pos="-1Cc 30 75% 24" posRelativeX="2c65e22a40bc686b"
              posRelativeW="2c65e22a40bc686b" posRelativeH="2c65e22a40bc686b"
              buttonText="Palette" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GROUPCOMPONENT name="layerGroup" id="ddc968defcd189da" memberName="layerGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 250 100% 250" title="Image"
                  textpos="33"/>
  <SLIDER name="brushSlider" id="aba3384d7b3a6f33" memberName="brushSlider"
          virtualName="" explicitFocusOrder="0" pos="-1Cc 75 75% 150" posRelativeX="2c65e22a40bc686b"
          posRelativeY="2c65e22a40bc686b" posRelativeW="2c65e22a40bc686b"
          min="1.0" max="4.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="3b1a81302236db98" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 20 150 50" posRelativeX="aba3384d7b3a6f33"
         posRelativeY="aba3384d7b3a6f33" edTextCol="ff000000" edBkgCol="0"
         labelText="Brush&#10;Size" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

