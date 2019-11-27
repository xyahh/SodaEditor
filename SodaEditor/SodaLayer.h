// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include "SodaGraphics.h"

BEGIN_SODA

/*
Soda Layer
@ Provides the Core functionality of Sprite Drawing. 
@ Layers are placed on a list and are drawn in that order.
@ Layer Ordering can change, which causes final image to change as well.
*/

class SodaLayer
{
public:

	SodaLayer(int Width, int Height) 
		: bIsVisible(true) , Bitmap(Width, Height, PixelFormat32bppARGB)
	{
	}

	/* SodaImage (i.e. CImage) handles deallocation automatically, so nothing to be called in Dtor */
	~SodaLayer()
	{
	}

	// Called when the Layer is Created
	bool OnCreate();

	// Renders  the Layer on the Window Specified
	void Render(SodaGraphics* Graphics);
	
	void Draw(int PixelX, int PixelY, const SodaColor& _Color);

	//Called at Fixed Delta Times
	void Update(float DeltaTime) {}

	// Called when the Layer is Destroyed
	void OnDestroy() {}

	// Called when the Layer is Focused (Set as Active)
	void OnFocusGained();

	//Called when another Layer is focused (another one set as active)
	void OnFocusLost();

	/*
	Returns the Current Visibility of the Layer.
	@ True -> Visible.
	@ False -> Hidden
	*/
	bool GetVisibility() const;

	/* 
	Toggles the Visibility of the Layer. Whether to Draw it or not.
	@ RETURN: The new Visibility
	@ True -> Visible.
	@ False -> Hidden
	*/
	bool ToggleVisibility();

private:

	SodaBitmap	Bitmap;
	bool		bIsVisible;

};

END_SODA