/*
  ==============================================================================

    SodaCommand.cpp
    Created: 2 Dec 2019 8:38:30pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaCommand.h"
#include "SodaCanvas.h"

/*
==============================================================================
Draw Command
==============================================================================
*/

bool FSodaDrawCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;

	//find the layer behind the id given
	SodaLayer* layer;
	if (false == canvas->getLayer(layer_id, &layer)) return false;
	Image* image = layer->getLayerImage();

	//set the new color of the pixel
	for (auto& pixel : Pixels)
		image->setPixelAt(pixel.x, pixel.y, pixel.newColour);
	return true;
}

bool FSodaDrawCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;

	//find the layer behind the id given
	SodaLayer* layer;
	if (false == canvas->getLayer(layer_id, &layer)) return false;
	Image* image = layer->getLayerImage();

	//set the old color of the pixel
	for (auto& pixel : Pixels)
		image->setPixelAt(pixel.x, pixel.y, pixel.oldColour);
	return true;
}

//if there's no new pixels to add, then we don't do anything

bool FSodaDrawCommand::isValid() const
{
	return !Pixels.empty();
}


/*
==============================================================================
Create Layer Command
==============================================================================
*/
bool FSodaCreateLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;

	Image* pImage = nullptr;
	if (validImage)
		pImage = &image;
	return canvas->createLayer_CommandCalled(id, pImage);
}

bool FSodaCreateLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;

	Image* pImage = nullptr;
	if (validImage)
		pImage = &image;

	return canvas->deleteLayer_CommandCalled(id, pImage);
}


/*
==============================================================================
Delete Layer Command
==============================================================================
*/

bool FSodaDeleteLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->deleteLayer_CommandCalled(id, &image);
}

bool FSodaDeleteLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->createLayer_CommandCalled(id, &image);
}

