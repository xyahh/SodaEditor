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

private:
	/* Hide to avoid other Mis-initializations/deletions*/
	SodaCanvas();
	~SodaCanvas();

public:

	static SodaCanvas* Get();

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

private:

	/*
	Layers are drawn from Begin to End 
	i.e. a layer with a higher index will be drawn over
	a layer with lower index
	*/
	STD vector<SodaLayer> Layers;

	/*
	Indicator of the Index of the currently Active Layer.
	When drawing, on the Screen, it will only draw in the 
	Active Layer.
	*/
	size_t ActiveLayer;

};

END_SODA