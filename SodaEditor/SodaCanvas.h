// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include "SodaLayer.h"
#include "SodaPalette.h"

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
	SodaCanvas(LONG Width = 64, LONG Height = 64);

	~SodaCanvas() 
	{
		//Remove all Layers safely
		Reset(0);
	}

public:
	
	/* Sets the Canvas Size to a new Height and Width. 
	@ This Function also 
	*/
	void UpdateCanvasSize(LONG Width, LONG Height);
	
	/*
	Updates the Pixel Size (Scale of the Pixel)
	*/
	void UpdatePixelSize(LONG PixelSize);

private:

	/*
	Updates CanvasSizeX and CanvasSizeY to match half of the Canvas Size 
	@ Used so that we don't calculate this every draw call but only when it has changed.
	*/
	void UpdateCanvasParameters();

public:

	/*
	Draws the Canvas, the Layers in order from 0 to N, and then the Grid Space (if Visible)
	*/
	void Draw();

	/*
	Deallocates all Existing Layers, and adds a new set of layers specified by the
	StartingLayerCount variable
	@param size_t StartingLayerCount: Count of Layers to Allocate. 
	If 0, this will only deallocate existing layers (no further layers are added)
	*/
	void Reset(size_t StartingLayerCount = 1);
	
	/*
	Deactivates the Current Active layer and then 
	Sets the layer in the Specified index as Active.
	*/
	void SetActiveLayer(size_t Index);

	/*
	Sets the Window where the Canvas will be drawn.
	This Window's Delegates will all be unbound first (using UnbindAll)
	and then the Canvas will bind the necesary functionality to its functions 
	(e.g. OnMouseClicked to handle where the Mouse was clicked in the canvas)
	*/
	void SetWindow(SodaWindow* Window);

	/*
	Sets the Palette that will be used to Change the Colors of the User's 'pen'
	*/
	void SetPalette(SodaPalette* Palette);

	/*
	Calculates the Rect that the Canvas will Ocuppy in the Window
	and assigns it to each of the variables pointed by the parameter pointers specified
	*/
	void GetCanvasRect(LONG* StartX, LONG* StartY, LONG* EndX, LONG* EndY);

	/*
	Inserts a Layer to the Array of Layers
	@ By Default it is emplaced at the back.
	@ Updates the ActiveLayer to the one that was just emplaced

	*/
	void CreateLayer();

	/*
	Function to handle the Mouse Click.
	@ int X, int Y -> Coordinates of the Mouse in the Window Space (this is then processed to Canvas Space)
	@ int Key -> key that was used in the Click (e.g. Right Click, or Left Click)
	@ bool IsPressed -> Whether the trigger Key was pressed (true) or released (false)
	*/
	void ProcessMouseEvent(int X, int Y, int Key, bool IsPressed);

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


private:

	SodaWindow* CanvasWindow;
	SodaPalette* CanvasPalette;

	// The size of the Canvas (i.e. how many pixels the Canvas has)
	LONG	CanvasSizeX;
	LONG	CanvasSizeY;

	// The Color used to clear the Canvas (starting color before drawing takes place)
	SodaColor	ClearColor;
	// The Color used to draw the Grid Lines. This will almost likely be the Inverse of Clear Color (i.e. ~ClearColor)
	SodaColor	GridColor;
	// The Selected Color. This is Gotten from a Soda Palette Class Instance.
	SodaColor	SelectedColor;

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

	/*
	the Size of the Pixels of the Canvas that is drawn into the Window.
	We can think of it as the 'Zoom' of the Canvas
	or ratio of the real pixels to the Sprite Pixel
	*/
	LONG PixelSize;

	/* 
	@ Going to become Member Variables to avoid having to recompute them
	@ every frame. Instead, recompute them only when the Canvas/Windows have been resized
	*/
	LONG WinHalfSizeX, WinHalfSizeY;
	LONG ScaledCanvasHalfSizeX, ScaledCanvasHalfSizeY;

	/*
	@ An Integer where each Bit represents the state of a Mouse Key.
	@ LBUTTON 0x1, RBUTTON 0x2, MBUTTON 0x4
	*/
	int MouseKeyStates;

	//Whether to Draw the Grid Space on top of the Sprite or Not
	bool bDrawGridLines;

};

END_SODA