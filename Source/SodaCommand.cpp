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
Activate Layer Command
==============================================================================
*/


bool FSodaActivateLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;
	prevActiveLayerValid = canvas->getActiveLayer(&prevActiveLayer);
	if (!canvas->setActiveLayer(layerToActivate))
		return false;
	return true;
}

bool FSodaActivateLayerCommand::undo(SodaCanvas * canvas)
{
	//check if the previous layer was a valid one
	if (prevActiveLayerValid  && canvas)
		return canvas->setActiveLayer(prevActiveLayer);
	return false;
}


/*
==============================================================================
Create Layer Command
==============================================================================
*/
bool FSodaCreateLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->createLayer(id);
}

bool FSodaCreateLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;
	return canvas->deleteLayer(id);
}


/*
==============================================================================
Delete Layer Command
==============================================================================
*/

bool FSodaDeleteLayerCommand::execute(SodaCanvas * canvas)
{
	if (!canvas) return false;
	SodaLayer* pLayer;
	if (canvas->getLayer(id, &pLayer))
	{
		//save a copy of the image before deleting so that we can restore if we undo
		image = pLayer->getLayerImage()->createCopy();
		return canvas->deleteLayer(id);
	}
	return false;
}

bool FSodaDeleteLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;
	SodaLayer* pLayer;
	if (!canvas->createLayer(id))
		return false;
	if (canvas->getLayer(id, &pLayer))
	{
		//restore the image 
		(*pLayer->getLayerImage()) = image.createCopy();
	}
}
