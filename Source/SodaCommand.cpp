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
	Index = canvas->createLayer();
	return true;
}

bool FSodaCreateLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;
	canvas->deleteLayer(Index);
	return true;
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
	if (canvas->getLayer(Index, &pLayer))
	{
		//save a copy of the image before deleting so that we can restore if we undo
		image = pLayer->getLayerImage()->createCopy();
		canvas->deleteLayer(Index);
		return true;
	}
	return false;
}

bool FSodaDeleteLayerCommand::undo(SodaCanvas * canvas)
{
	if (!canvas) return false;
	SodaLayer* pLayer;
	Index = canvas->createLayer();
	if (canvas->getLayer(Index, &pLayer))
	{
		//restore the image 
		(*pLayer->getLayerImage()) = image.createCopy();
	}
}
