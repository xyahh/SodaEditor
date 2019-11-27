// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaLayer.h"
#include "SodaWindow.h"

USE_SODA;

SodaLayer::SodaLayer()
{
}


SodaLayer::~SodaLayer()
{
}

// Draws the Layer on the Window Specified

void SodaLayer::Draw(SodaWindow * Window) 
{
	Window->ClearScreen(ClearColor);

}

void SodaLayer::OnFocusGained()
{
}

void SodaLayer::OnFocusLost()
{
}

void SodaLayer::SetVisibility(bool Visibility)
{
	bIsVisible = Visibility;
}

void SodaLayer::SetClearColor(FVectorParam1 _ClearColor)
{
	ClearColor = StoreFloat4(_ClearColor);
}
