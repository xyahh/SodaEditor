// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once

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
	SodaLayer();
	~SodaLayer();

	// Called when the Layer is Created
	void OnCreate() {}

	// Draws the Layer on the Window Specified
	void Draw(SodaWindow* Window);
	
	//Called at Fixed Delta Times
	void Update(float DeltaTime) {}

	// Called when the Layer is Destroyed
	void OnDestroy() {}

	// Called when the Layer is Focused (Set as Active)
	void OnFocusGained();

	//Called when another Layer is focused (another one set as active)
	void OnFocusLost();

	/* 
	Sets the Visibility of the Layer. Whether to Draw it or not.
	@ bool Visibility -> true to Show, false to Hide
	*/
	void SetVisibility(bool Visibility);

	/*
	Sets the Color which to use whn clearing the Layer Screen
	@ Float4 _ClearColor -> the Clear Color in the format (R, G, B, A)
	*/
	void SetClearColor(FVectorParam1 _ClearColor);

private:

	Float4	ClearColor;
	bool	bIsVisible;

};

END_SODA