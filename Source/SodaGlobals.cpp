/*
  ==============================================================================

    SodaGlobals.cpp
    Created: 30 Nov 2019 9:26:49pm
    Author:  Juan

  ==============================================================================
*/

#include "SodaGlobals.h"
#include "SodaCanvas.h"

FSodaProperties gProperties;

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
