// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"

#include "SodaWindow.h"
#include "SodaCanvas.h"

int main()
{
	SODA SodaWindow* MainWindow = new SODA SodaWindow(TEXT("Soda Editor, 2019"), 800, 800);
	MainWindow->StartWindow();

	SODA SodaWindow* ToolboxWindow = new SODA SodaWindow(TEXT("Soda Toolbox"), 300, 300);
	ToolboxWindow->StartWindow();

	SODA SodaCanvas* Canvas = new SODA SodaCanvas;
	Canvas->SetClearColor({ 0xFF, 0x00, 0x00, 0xFF });
	Canvas->Reset(1); // Start with One Layer;

	while (MainWindow->ProcessMessage())
	{
		Canvas->Draw(MainWindow);
	}
	
	delete Canvas;
	delete ToolboxWindow;
	delete MainWindow;
}