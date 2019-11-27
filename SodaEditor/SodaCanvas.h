// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include "SodaLayer.h"

BEGIN_SODA

/*
Soda Canvas
@ Class to represent the Collection of Layers and handles
@ Which Layer is Active and the reordering of these layers.
*/
class SodaCanvas
{
	//Hiding Ctor & Dtor to Allow only One Canvas to be Present at a time.
public:

	// Default Canvas/Sprite Size will be 64x64
	// Default Color is White (Alpha 1)
	SodaCanvas(Uint2 Size = { 64, 64 })
		: CanvasSize(Size)
		, ClearColor({ 0xFF, 0xFF, 0xFF, 0xFF }) //White
	{
	}

	~SodaCanvas() 
	{
		//Remove all Layers safely
		Reset(0);
	}

public:

	void Draw(SodaWindow* Window);

	void Reset(size_t StartingLayerCount = 1);
	
	void SetActiveLayer(size_t Index);

	/*
	Inserts a Layer to the Array of Layers
	@ By Default it is emplaced at the back.
	@ Updates the ActiveLayer to the one that was just emplaced
	*/
	void CreateLayer();


	/*
	Destroys a Layer at a Given Index.
	If it was the Active Layer, a new Active Layer
	will be set
	*/
	void DestroyLayer(size_t Index);

	/*
	Sets the Color which to use whn clearing the Layer Screen
	@ Float4 _ClearColor -> the Clear Color in the format (R, G, B, A)
	*/
	void SetClearColor(const SodaColor& _ClearColor);

private:

	/*
	Called when a New Layer has been Created/Emplaced.
	@ This func sets the new layer as active and calls OnCreatedFunc
	*/
	void LayerCreated();


private:

	// The size of the Canvas (i.e. how many pixels the Canvas has)
	Uint2	CanvasSize;

	// The Color used to clear the Canvas (starting color before drawing takes place)
	SodaColor	ClearColor;

	/*
	Layers are drawn from Begin to End 
	i.e. a layer with a higher index will be drawn over
	a layer with lower index
	*/
	STD vector<SodaLayer*> Layers;

	/*
	Indicator of the Index of the currently Active Layer.
	When drawing, on the Screen, it will only draw in the 
	Active Layer.
	*/
	size_t ActiveLayer;

};

END_SODA