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
#include "SodaGlobals.h"
//[/MiscUserDefs]

//==============================================================================
SodaLayer::SodaLayer (int width_, int height_, int pixelSize_)
    : layer_width(width_),
      layer_height(height_),
      layer_pixelSize(pixelSize_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

	//Creating an Image of Width * Height and ARGB format
	//layer_image = Image(Image::RGB, layer_width, layer_height, true);
	isDrawing = false;
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
	//avoid calc if these two are the same
	if (PreviousMouseCoords == CurrentMouseCoords) return;
	if (!isDrawing) return;

	//Convert the Previous Mouse Coords and Current to start the line check
	auto StartPoint = ConvertPosition(PreviousMouseCoords).toFloat();
	auto EndPoint = ConvertPosition(CurrentMouseCoords).toFloat();
	auto PivotPoint = ConvertPosition(PivotMouseCoords).toFloat();

	PreviousMouseCoords = CurrentMouseCoords;

	//proc behavior of what we just calculated depending on the currentBrush
	switch (gCurrentProperties.currentBrush)
	{
	case ESodaShapes::FreeStyle:
	{
		auto Vector = EndPoint - StartPoint;
		//normalize the direction of the Vector from Prev->Curr
		float Dist = Vector.getDistanceFromOrigin();

		Vector /= Dist;
		//set the Color of the pixel at each square that we came across from Start to End
		for (float i = 0.f; i <= Dist; i += 0.25f)
			drawPixel(StartPoint.x + Vector.x * i, StartPoint.y + Vector.y*i, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
	}
	break;
	//Mid-Point Circle Drawing Algorithm.
	//code source: https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
	case ESodaShapes::Circle:
	{
		auto Vector = EndPoint - PivotPoint;
		//normalize the direction of the Vector from Pivot->Curr
		float Dist = Vector.getDistanceFromOrigin();
		resetDrawings();
		if (Dist >= 10)
			Dist = Dist;
		int x = Dist, y = 0;
		int P = 1 - Dist;
		while (x > y)
		{
			++y;
			// Mid-point is inside or on the perimeter
			if (P <= 0)
				P = P + 2 * y + 1;
			// Mid-point is outside the perimeter
			else
			{
				--x;
				P = P + 2 * y - 2 * x + 1;
			}
			// All the perimeter points have already been printed
			if (x < y)
				break;

			// Drawing the generated point and its reflection
			// in the other octants after translation
			drawPixel(+x + PivotPoint.x, +y + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
			drawPixel(-x + PivotPoint.x, +y + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
			drawPixel(+x + PivotPoint.x, -y + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
			drawPixel(-x + PivotPoint.x, -y + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
			// If the generated point is on the line x = y then
			// the perimeter points have already been printed
			if (x != y)
			{
				drawPixel(+y + PivotPoint.x, +x + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
				drawPixel(-y + PivotPoint.x, +x + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
				drawPixel(+y + PivotPoint.x, -x + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
				drawPixel(-y + PivotPoint.x, -x + PivotPoint.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
			}
		}



		break;
	}
	case ESodaShapes::Rectangle:
		break;
	}





}

void SodaLayer::startDraw(const MouseEvent & e)
{
	NewPixels.clear();
	OldPixels.clear();

	CurrentMouseCoords = e.getPosition();
	PreviousMouseCoords = CurrentMouseCoords;
	PivotMouseCoords = CurrentMouseCoords;

	//draw the first pixel
	auto Coord = ConvertPosition(PreviousMouseCoords);
	drawPixel(Coord.x, Coord.y, gCurrentProperties.brushSize, gCurrentProperties.brushColour);
	isDrawing = true;
}

void SodaLayer::draw(const MouseEvent & e)
{
	CurrentMouseCoords = e.getPosition();
}

void SodaLayer::resetDrawings()
{
	FSodaDrawCommand drawCommand(&image, std::move(NewPixels), std::move(OldPixels));
	drawCommand.undo(nullptr);
}

void SodaLayer::endDraw(const MouseEvent & e, std::set<FPixel>* outNewPixels, std::set<FPixel>* outOldPixels)
{
	isDrawing = false;
	*outNewPixels = std::move(NewPixels);
	*outOldPixels = std::move(OldPixels);
	resetDrawings();
}

void SodaLayer::drawPixel(int X, int Y, int brushSize, const Colour & colour)
{
	int rangeY = (brushSize - 1);
	for (int dy = -rangeY; dy <= rangeY; ++dy)
	{
		int rangeX = (2 * (brushSize - abs(dy)) - 1) / 2;
		for (int dx = -rangeX; dx <= rangeX; ++ dx)
		{
			int px = X + dx;
			int py = Y + dy;
			OldPixels.emplace(px, py, image.getPixelAt(px, py));
			image.setPixelAt(px, py, colour);
			NewPixels.emplace(px, py, colour);
		}
	}
}

Point<int> SodaLayer::ConvertPosition(const Point<int>& Pos)
{
	//Convert the Points to float as we are going to have some bit of floating point Calculation
	auto Coords = Pos.toFloat();

	//gets the Bounds of the current Component
	Rectangle<float> rect = getBounds().toFloat();

	// reduce top left to 0,0, divide by current component size and then multiply by layer dimensions
	Coords -= rect.getTopLeft();
	Coords /= Point<float>(rect.getWidth(), rect.getHeight());
	Coords *= Point<float>(layer_width, layer_height);

	return Coords.toInt();
}

Image * SodaLayer::getLayerImage()
{
	return &image;
}

void SodaLayer::onActivation()
{
	/* Set the current pointer to the image being drawn */
	gCurrentProperties.currentImage = &image;
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SodaLayer" componentName=""
                 parentClasses="public Component" constructorParams="int width_, int height_, int pixelSize_"
                 variableInitialisers="layer_width(width_),&#10;layer_height(height_),&#10;layer_pixelSize(pixelSize_)&#10;&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

