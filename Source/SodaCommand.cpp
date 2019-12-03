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
	return canvas->createLayer_Internal(id, pImage);
}

bool FSodaCreateLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;

	Image* pImage = nullptr;
	if (validImage)
		pImage = &image;

	return canvas->deleteLayer_Internal(id, pImage);
}


/*
==============================================================================
Delete Layer Command
==============================================================================
*/

bool FSodaDeleteLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->deleteLayer_Internal(id, &image);
}

bool FSodaDeleteLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->createLayer_Internal(id, &image);
}

/*
==============================================================================
Activate Layer Command
==============================================================================
*/

FSodaActivateLayerCommand::FSodaActivateLayerCommand(size_t id_) : id(id_) 
{
	prevIDset = false;
}

bool FSodaActivateLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;

	if (!prevIDset)
	{
		canvas->getActiveLayerID(&prev_id);
		prevIDset = true;
	}

	return canvas->setActiveLayer_Internal(id);
}

bool FSodaActivateLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->setActiveLayer_Internal(prev_id);
}


/*
==============================================================================
Swap Layer Command
==============================================================================
*/


bool FSodaMoveLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->moveLayer_Internal(target, destination, placeBeforeDestination);
}

bool FSodaMoveLayerCommand::undo(SodaCanvas * canvas)
{
	//Swapping Layers from A<->B and back is the same process so
	//we just call execute
	return execute(canvas);
}
