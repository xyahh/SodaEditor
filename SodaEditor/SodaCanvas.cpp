// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaCanvas.h"
#include "SodaWindow.h"

USE_SODA;

SodaCanvas::SodaCanvas(LONG Width, LONG Height)
	: CanvasSizeX(Width)
	, CanvasSizeY(Height)
	, bDrawGridLines(true)
	, PixelSize(8)
	, ClearColor(SodaColor::White) // Def Clear Color: White
	, SelectedColor(SodaColor::Black) // Def Selected Color: Black;
	, CanvasWindow(nullptr)
	, CanvasPalette(nullptr)
{
	UpdateCanvasParameters();
}

void SodaCanvas::UpdateCanvasSize(LONG Width, LONG Height)
{
	CanvasSizeX = Width;
	CanvasSizeY = Height;
	UpdateCanvasParameters();
}

void SodaCanvas::UpdatePixelSize(LONG PixelSize_)
{
	PixelSize = PixelSize_;
}

void SodaCanvas::UpdateCanvasParameters()
{
	//Calculate the Half Size of the Canvas for Convenience
	ScaledCanvasHalfSizeX = PixelSize * CanvasSizeX / 2;
	ScaledCanvasHalfSizeY = PixelSize *CanvasSizeY / 2;
}

void SodaCanvas::Draw()
{
	if (!CanvasWindow) return;

	SodaGraphics* Graphics = CanvasWindow->MakeGraphics();

	/* Set the Graphics for Pixel Sprite Drawing */
	Graphics->SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHighQuality);
	Graphics->SetSmoothingMode(SodaSmoothing::SmoothingModeNone);
	Graphics->SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeNearestNeighbor);

	////Clear Canvas with ClearColor
	Graphics->Clear(ClearColor);
	
	LONG StartX, StartY;
	LONG EndX, EndY;
	GetCanvasRect(&StartX, &StartY, &EndX, &EndY);

	//// Draw each Layer from 0 sequentially on top of each other
	for (auto& Layer : Layers)
		Layer->Render(Graphics, StartX, StartY, ScaledCanvasHalfSizeX * 2, ScaledCanvasHalfSizeY * 2);

	//Draw Grid Opposite to the Clear Color
	if (bDrawGridLines)
	{
		SodaPen   Pen(GridColor);
		//Draw Columns
		for (LONG x = StartX; x <= PixelSize * CanvasSizeX + StartX;  x += PixelSize)
			Graphics->DrawLine(&Pen, x, StartY, x, EndY);
		//Draw Rows
		for (LONG y = StartY; y <= PixelSize * CanvasSizeY + StartY;  y += PixelSize)
			Graphics->DrawLine(&Pen, StartX, y, EndX, y);
	}
	
	//Dispose of Graphics once we've drawn all
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
		Layers.emplace_back(new SodaLayer(CanvasSizeX, CanvasSizeY));

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
	//Make sure we have at least one layer. 
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

void SodaCanvas::SetWindow(SodaWindow * Window)
{
	Window->UnbindAllDelegates();

	//if we had a previous Window bound, unbind all delegates from that window
	//(process here if we want to close that previous Window)
	if (CanvasWindow) CanvasWindow->UnbindAllDelegates();

	CanvasWindow = Window;
	CanvasWindow->OnMouseProc.Bind([&](int MouseX, int MouseY, int Key, bool IsPressed)
	{
		ProcessMouseEvent(MouseX, MouseY, Key, IsPressed);
	});

	//Updates WinHalfSizes. Canvas Size stays the same.
	CanvasWindow->OnWindowResized.Bind([&](int Width, int Height)
	{
		WinHalfSizeX = Width / 2;
		WinHalfSizeY = Height/ 2;
	});

}

void SodaCanvas::SetPalette(SodaPalette * Palette)
{
	Palette->OnColorSelected.UnbindAll();
	if (CanvasPalette) CanvasPalette->OnColorSelected.UnbindAll();
	CanvasPalette = Palette;
	CanvasPalette->OnColorSelected.Bind([&](const SodaColor& Color)
	{
		//Update the Drawing Color to the Color that the Palette gives us!
		SelectedColor = Color;
	});
}

void SodaCanvas::GetCanvasRect(LONG * StartX, LONG * StartY, LONG * EndX, LONG * EndY)
{
	// Left Upper Most Coordinate of the Canvas
	*StartX = WinHalfSizeX - ScaledCanvasHalfSizeX;
	*StartY = WinHalfSizeY - ScaledCanvasHalfSizeY;

	// Right Lower Most Coordinate of the Canvas
	*EndY = WinHalfSizeY + ScaledCanvasHalfSizeY;
	*EndX = WinHalfSizeX + ScaledCanvasHalfSizeX;
}

void SodaCanvas::CreateLayer()
{
	//Layer Constructor consists of Width & Height of the Bitmap.
	// Make it the Same size as the Canvas
	Layers.emplace_back(new SodaLayer(CanvasSizeX, CanvasSizeY));

	//Call On Create on Added Layer and Set as Active
	(*Layers.rend())->OnCreate();
	SetActiveLayer(Layers.size() - 1);
}

void SodaCanvas::ProcessMouseEvent(int X, int Y, int Key, bool IsPressed)
{
	if (!Key) return;

	LONG StartX, StartY;
	LONG EndX, EndY;

	GetCanvasRect(&StartX, &StartY, &EndX, &EndY);

	//Calculate which Pixel was Clicked
	int PixelX = (X - StartX) / PixelSize;
	int PixelY = (Y - StartY) / PixelSize;

	if (IsPressed)
		MouseKeyStates |= Key;
	else
		MouseKeyStates &= ~Key;
	
	switch (Key)
	{
	case VK_LBUTTON:
	{
		if (IsPressed)
			Layers[ActiveLayer]->SetPixelColor(PixelX, PixelY, SelectedColor);
		break;
	}
	case VK_RBUTTON:
	{
		if (IsPressed)
			Layers[ActiveLayer]->SetPixelColor(PixelX, PixelY, ClearColor);
		break;
	}
	}
}

void SodaCanvas::DestroyLayer(size_t Index)
{
}

void SodaCanvas::SetClearColor(const SodaColor& ClearColor_)
{
	ClearColor = ClearColor_;
	GridColor = SodaColor(
		//Grid will always Be Visible!
		0xFF,
		//Invert the Clear Color so we always see the Line!
		~ClearColor.GetR(),
		~ClearColor.GetG(),
		~ClearColor.GetB()
	);
}
