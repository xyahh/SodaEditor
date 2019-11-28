#include "stdafx.h"
#include "SodaPalette.h"
#include "SodaWindow.h"

USE_SODA;

SodaPalette::SodaPalette()
{
}


SodaPalette::~SodaPalette()
{
}

void SodaPalette::SetWindow(SodaWindow * Window)
{
	PaletteWindow = Window;
	PaletteWindow->OnMouseProc.Bind([this](int X, int Y, int Key, bool IsPressed)
	{
		OnMouseClick(X, Y, Key, IsPressed);
	});
}

void SodaPalette::OnMouseClick(int X, int Y, int Key, bool IsPressed)
{
	SodaColor ColorSelected;

	//Calculate Color
	switch (rand() % 5)
	{
	case 0:
		ColorSelected = SodaColor::Black;
		break;
	case 1:
		ColorSelected = SodaColor::Red;
		break;
	case 2:
		ColorSelected = SodaColor::Blue;
		break;
	case 3:
		ColorSelected = SodaColor::Green;
		break;
	case 4:
		ColorSelected = SodaColor::Yellow;
		break;
	}
	OnColorSelected.Call(ColorSelected);
}

void SodaPalette::Draw()
{
}
