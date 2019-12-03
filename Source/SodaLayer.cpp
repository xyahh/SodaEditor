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

#include "SodaLayer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "SodaBrush.h"
//[/MiscUserDefs]

//==============================================================================
SodaLayer::SodaLayer (int width_, int height_)
    : layer_width(width_),
      layer_height(height_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
	setSize(layer_width, layer_height);
	//Creating an Image of Width * Height and ARGB format
	image = Image(Image::ARGB, layer_width, layer_height, true);
    //[/Constructor]
}

SodaLayer::~SodaLayer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SodaLayer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
	//Graphics gr(image);
	g.setColour(Colours::black);
	g.drawRect(getBounds(), 1.f);
	g.drawImage(image, getBounds().toFloat());
    //[/UserPaint]
}

void SodaLayer::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void SodaLayer::update()
{
	if (gProperties.brush)
		gProperties.brush->updateDraw(&image, ConvertPosition(CurrentMousePosition));
}

void SodaLayer::startDraw(const MouseEvent & e)
{
	//draw the first pixel
	CurrentMousePosition = e.getPosition();
	if (gProperties.brush)
		gProperties.brush->startDraw(&image, ConvertPosition(CurrentMousePosition));
}

void SodaLayer::updateMousePos(const MouseEvent & e)
{
	CurrentMousePosition = e.getPosition();
}

void SodaLayer::endDraw(const MouseEvent & e, std::set<FPixel>* outPixels)
{
	if (gProperties.brush)
		gProperties.brush->endDraw(&image, outPixels);
}

Point<float> SodaLayer::ConvertPosition(const Point<int>& Pos)
{
	//Convert the Points to float as we are going to have some bit of floating point Calculation
	auto Coords = Pos.toFloat();

	//gets the Bounds of the current Component
	Rectangle<float> rect = getBounds().toFloat();

	// reduce top left to 0,0, divide by current component size and then multiply by layer dimensions
	Coords -= rect.getTopLeft();
	Coords /= Point<float>(rect.getWidth(), rect.getHeight());
	Coords *= Point<float>(layer_width, layer_height);

	return Coords;
}

Image * SodaLayer::getLayerImage()
{
	return &image;
}

void SodaLayer::onActivation()
{
	/* Set the current pointer to the image being drawn */
	gProperties.image = &image;
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SodaLayer" componentName=""
                 parentClasses="public Component" constructorParams="int width_, int height_"
                 variableInitialisers="layer_width(width_),&#10;layer_height(height_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

