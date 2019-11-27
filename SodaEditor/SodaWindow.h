// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include "SodaGraphics.h"

BEGIN_SODA

class SodaWindow
{
public:

	SodaWindow(const FString& WindowTitle, int Width, int Height);
	virtual ~SodaWindow();

	/*
	@ Made public & static so that Windows API can always call it.
	@ In this Func, the local WndProc is called for more specific work.
	*/
	static LRESULT CALLBACK GlobalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/*
	@ Checks if there are any Messages for Windows API
	@ if there are and there is no QUIT message, then continue (return true)
	*/
	bool ProcessMessage();

	void SwapBuffers();

	/*
	Calls the ShowWindow, and Focus Window and Update Window functionjs
	*/
	void StartWindow();

	/*
	Generates a New Soda Graphics. 
	@ Deallocation must take place after use! (delete Graphics!)
	*/
	SodaGraphics* MakeGraphics();

	/*
	Gets the current position of the Mouse Relative to the Window calling it
	*/
	void GetCursorPosition(int* outX, int* outY) const;

protected:

	/*
	@ Local WndProc called by GlobalWndProc. Can be overriden by another Child Windows
	*/
	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	ULONG_PTR		SodaGraphicsToken = 0;

	RECT			WindowRect;

	FString			WindowTitle;
	Uint2			WindowSize;

	HINSTANCE		hInstance;
	MSG				Msg;
	HWND			hWnd;

	HDC				hDC;
};

END_SODA