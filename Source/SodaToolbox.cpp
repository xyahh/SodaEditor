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
    : listBoxModel(listBox, itemData)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    imagePreview.reset (new GroupComponent ("imagePreview",
                                            TRANS("Preview")));
    addAndMakeVisible (imagePreview.get());

    layerGroup.reset (new GroupComponent ("layerGroup",
                                          TRANS("Layers")));
    addAndMakeVisible (layerGroup.get());

    createLayerButton.reset (new TextButton ("createLayerButton"));
    addAndMakeVisible (createLayerButton.get());
    createLayerButton->setButtonText (TRANS("Create Layer"));
    createLayerButton->addListener (this);
    createLayerButton->setColour (TextButton::buttonColourId, Colour (0x20ffffff));


    //[UserPreSize]

	sodaCanvas = canvas_;
	listBoxModel.setCanvas(sodaCanvas);

	//default item
	auto item = new LayerListBoxItemData::FLayerInfo("Layer #0", true);
	item->layerIndex = 0;

	itemData.layerInfo.add(item);
	listBox.updateContent();

	listBox.setModel(&listBoxModel);
	//height for each layer item
	listBox.setRowHeight(40);
	//colour of the whole list background 
	listBox.setColour(ListBox::backgroundColourId, Colour::fromFloatRGBA(0.1f, 0.1f, 0.1f, 0.1f));
	addAndMakeVisible(listBox);

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
    layerGroup = nullptr;
    createLayerButton = nullptr;


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
	if (gProperties.image)
	{
		g.setImageResamplingQuality(Graphics::ResamplingQuality::lowResamplingQuality);
		g.drawImage(*gProperties.image, previewRectangle, RectanglePlacement::centred);
	}


    //[/UserPaint]
}

void SodaToolbox::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    imagePreview->setBounds (0, 0, proportionOfWidth (1.0000f), 256);
    layerGroup->setBounds (0, 266, proportionOfWidth (1.0000f), getHeight() - 235);
    createLayerButton->setBounds (0 + proportionOfWidth (1.0000f) / 2 - ((proportionOfWidth (1.0000f) - 60) / 2), 266 + 30, proportionOfWidth (1.0000f) - 60, 30);
    //[UserResized] Add your own custom resize handling here..
	auto imagePreviewRect = imagePreview->getBounds().toFloat();
	listBox.setBounds (0 + 30, 266 + 90, proportionOfWidth (1.0000f) - 60, (getHeight() - 275) - 120);
	previewRectangle = imagePreviewRect * 0.9f;
	previewRectangle.setLeft(imagePreviewRect.getWidth() * 0.1f);
	previewRectangle.setTop(imagePreviewRect.getHeight() * 0.1f);
    //[/UserResized]
}

void SodaToolbox::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == createLayerButton.get())
    {
        //[UserButtonCode_createLayerButton] -- add your button handler code here..
		createLayer();
        //[/UserButtonCode_createLayerButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SodaToolbox::update()
{
}

void SodaToolbox::createLayer()
{
	static long long i = 1;
	auto item = new LayerListBoxItemData::FLayerInfo(String("Layer #") + String(i++), true);
	item->layerIndex = sodaCanvas->createLayer();
	itemData.layerInfo.add(item);
	listBox.updateContent();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SodaToolbox" componentName=""
                 parentClasses="public AnimatedAppComponent" constructorParams="SodaCanvas* canvas_"
                 variableInitialisers="listBoxModel(listBox, itemData)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff808080"/>
  <GROUPCOMPONENT name="imagePreview" id="8b984c2d2be3b733" memberName="imagePreview"
                  virtualName="" explicitFocusOrder="0" pos="0 0 100% 256" title="Preview"/>
  <GROUPCOMPONENT name="layerGroup" id="fdc7952107ea4195" memberName="layerGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 266 100% 235M" title="Layers"/>
  <TEXTBUTTON name="createLayerButton" id="5cd54010d3a7d2fc" memberName="createLayerButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc 30 60M 30" posRelativeX="fdc7952107ea4195"
              posRelativeY="fdc7952107ea4195" posRelativeW="fdc7952107ea4195"
              posRelativeH="fdc7952107ea4195" bgColOff="20ffffff" buttonText="Create Layer"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

