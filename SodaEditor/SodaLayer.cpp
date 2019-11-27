// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaLayer.h"
#include "SodaWindow.h"

USE_SODA;

// Called when the Layer is Created
bool SodaLayer::OnCreate()
{
	return true;
}

// Draws the Layer on the Window Specified
void SodaLayer::Render(SodaGraphics * Graphics)
{
	if (bIsVisible)
		Graphics->DrawImage(&Bitmap, 0, 0);
}

void SodaLayer::Draw(int PixelX, int PixelY, const SodaColor& _Color)
{
	Bitmap.SetPixel(PixelX, PixelY, SodaColor::MakeARGB
	(_Color.GetA(), _Color.GetR(), _Color.GetG(), _Color.GetB()));
}

void SodaLayer::OnFocusGained()
{
}

void SodaLayer::OnFocusLost()
{
}

bool SodaLayer::GetVisibility() const
{
	return bIsVisible;
}

bool SodaLayer::ToggleVisibility()
{
	bIsVisible = !bIsVisible;
	return bIsVisible;
}