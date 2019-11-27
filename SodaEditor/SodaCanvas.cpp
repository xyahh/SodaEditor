// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaCanvas.h"
#include "SodaWindow.h"

USE_SODA;

void SodaCanvas::Draw(SodaWindow* Window)
{
	SodaGraphics* Graphics = Window->MakeGraphics();

	////Clear Canvas with ClearColor
	Graphics->Clear(ClearColor);
	//
	//// Draw each Layer from 0 sequentially on top of each other
	//for (auto& Layer : Layers)
	//	Layer->Render(Graphics);

	Gdiplus::Pen      pen(SodaColor(255, 0, 0, 255));
	Graphics->DrawLine(&pen, 0, 0, 200, 100);

	delete Graphics;
}

void SodaCanvas::Reset(size_t StartingLayerCount)
{	
	// Call the OnDestroy func before Deallocating the Layers
	for (auto& Layer : Layers)
	{
		Layer->OnDestroy();
		delete Layer;
	}

	// Clear the Current Layers in the array and make 
	// new ones based on StartingLayerCount
	Layers.clear();

	//If the LayerCount is 0, we just Clean up Current Layers and return 
	if (StartingLayerCount == 0)
		return;

	//Resizing calls Default Constructor. Since SodaLayer doesn't have
	// def ctor, Reserve the amount and then FOR loop will be used to Init the layers
	Layers.reserve(StartingLayerCount);
	for (size_t i = 0; i < StartingLayerCount; ++i)
		Layers.emplace_back(new SodaLayer(CanvasSize.x, CanvasSize.y));

	// once we allocate the new layers, we call OnCreate for each
	for (auto& Layer : Layers)
		Layer->OnCreate();

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
	Layers[ActiveLayer]->OnFocusLost();
	ActiveLayer = Index;
	//Call OnFocusGained on newly Selected ActiveLayer
	Layers[ActiveLayer]->OnFocusGained();
}

void SodaCanvas::CreateLayer()
{
	//Layer Constructor consists of Width & Height of the Bitmap.
	// Make it the Same size as the Canvas
	Layers.emplace_back(new SodaLayer(CanvasSize.x, CanvasSize.y));
	LayerCreated();
}

void SodaCanvas::DestroyLayer(size_t Index)
{
}

void SodaCanvas::SetClearColor(const SodaColor& _ClearColor)
{
	ClearColor = _ClearColor;
}

void SodaCanvas::LayerCreated()
{
	//Call On Create on Added Layer and Activate it
	(*Layers.rend())->OnCreate();
	SetActiveLayer(Layers.size() - 1);
}
