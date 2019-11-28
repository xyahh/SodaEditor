#pragma once
#include "SodaGraphics.h"

BEGIN_SODA

class SodaPalette
{
public:
	SodaPalette();
	~SodaPalette();

	void SetWindow(SodaWindow* Window);

	/*
	Processes which Color the Palette has been Clicked and Calls
	the OnColorSelected Delegate
	*/
	void OnMouseClick(int X, int Y, int Key, bool IsPressed);
	
	void Draw();

	FDelegate<SodaColor> OnColorSelected;

private:

	SodaWindow* PaletteWindow;

};

END_SODA