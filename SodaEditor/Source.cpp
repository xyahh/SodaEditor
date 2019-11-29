// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"

#include "SodaCore.h"

#include "SodaWindow.h"
#include "SodaCanvas.h"

#include "SodaPalette.h"

/*
Placing this Functionality in the Main Window to Showcase
that we do not need a "Super" class that controls the Tick
*/

int main()
{

	//Graphic & Other Stuff Initialization
	SODA SodaCore Startup;

	//Initializing Soda Windows
	STD vector<SODA SodaWindow*> Windows 
	{
		new SODA SodaWindow	{ TEXT("Soda Editor")	, 0, 0, 640, 640					}, // Index 0 : The Main Window
		new SODA SodaWindow	{ TEXT("Palette")		, -320 - 100, -320 + 100, 200, 200	}, // Index 1 : Color Selection Window
		new SODA SodaWindow	{ TEXT("Preview")		,  320 + 150, -320 + 150, 300, 300	}  // Index 2 : Preview Window
	};

	SODA SodaPalette Palette;
	Palette.SetWindow(Windows[1]);

	SODA SodaCanvas Canvas;
	Canvas.SetWindow(Windows[0]);
	Canvas.SetPalette(&Palette);
	Canvas.Reset(1); // Start with One Layer;

	for (auto& Window : Windows)
		Window->StartWindow();

	// In future implementations, we can move this Loop into another program/framework
	// and port the SodaEditor as a Plugin
	while(true)
	{
		for (auto& Window : Windows)
			if (false == Window->ProcessMessage())
				return 0;
		Canvas.Draw();
		Palette.Draw();
		for (auto& Window : Windows)
			Window->SwapBuffers();
	}

	for (auto& Window : Windows)
	{
		delete Window;
		Window = nullptr;
	}

	return 0;

}