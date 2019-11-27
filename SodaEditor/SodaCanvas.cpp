// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaCanvas.h"

USE_SODA;

SodaCanvas::SodaCanvas()
{
}

SodaCanvas::~SodaCanvas()
{
}

SodaCanvas * SodaCanvas::Get()
{
	/* Thread safe initialization */
	static SodaCanvas* pInstance = new SodaCanvas;
	return pInstance;
}

void SodaCanvas::Reset(size_t StartingLayerCount)
{
	//Make sure we have at least 1 layer in the canvas
	if (StartingLayerCount <= 0)
		StartingLayerCount = 1;
	
	// Call the OnDestroy func before Deallocating the Layers
	for (auto& Layer : Layers)
		Layer.OnDestroy();

	// Clear the Current Layers in the array and make 
	// new ones based on StartingLayerCount
	Layers.clear();
	Layers.resize(StartingLayerCount);

	// once we allocate the new layers, we call OnCreate for each
	for (auto& Layer : Layers)
		Layer.OnCreate();

	size_t LastIndex = Layers.size() - 1;

	// Set the Active layer here without calling OnFocusLost 
	// because there are no layers anyways!
	ActiveLayer = LastIndex;
	// Set last added Layer as the Active one. 
	//(will call OnFocusLost and then OnFocusGained on Active Layer)
	SetActiveLayer(LastIndex);
}

void SodaCanvas::SetActiveLayer(size_t Index)
{
	if (Layers.empty()) return;

	size_t Zero = 0;
	/* Clamping to the Vector Range */
	Clamp(Zero, &Index, Layers.size() - 1);

	// Call OnFocusLost on Previously Selected ActiveLayer
	Layers[ActiveLayer].OnFocusLost();
	ActiveLayer = Index;
	//Call OnFocusGained on newly Selected ActiveLayer
	Layers[ActiveLayer].OnFocusGained();
}

void SodaCanvas::CreateLayer()
{
	Layers.emplace_back();
	//Call On Create on Added Layer
	Layers.rend()->OnCreate();
	SetActiveLayer(Layers.size() - 1);
}

void SodaCanvas::DestroyLayer(size_t Index)
{
}
