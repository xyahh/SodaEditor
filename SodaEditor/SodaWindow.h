// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include "SodaGraphics.h"

BEGIN_SODA

class SodaWindow
{
public:

	SodaWindow(const FString& WindowTitle, int CenterOffsetX, int CenterOffsetY, int Width, int Height);
	~SodaWindow();

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

	/*
	@ Gets the Current Window Size
	*/
	void GetWindowSize(LONG* X, LONG* Y);
	
	void CreateBackBuffer();
	void SwapBuffers();
	void ReleaseBackBuffer();

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

	/*
	On Mouse Click Delegate
	@ Is called everytime a Mouse Button is Pressed/Released or Moved
	@ param1 int: Position X of the Mouse
	@ param2 int: Position Y of the Mouse
	@ param3 int: Mouse Key that was Clicked/Released
	@ param4 bool: Key's state. Whether this Key was Pressed (true) or Released (false) (true if moving, as well)
	*/
	FDelegate<int, int, int, bool> OnMouseProc;

	/*
	On Window Resized Delegate
	@ Is called everytime the Window is Resized 
	@ param1 int: The new Width of the Window
	@ param2 int: The new Height of the Window
	*/
	FDelegate<int, int> OnWindowResized;

	/* A func that handles Unbinding all of the Functions bound to each SodaDelegate in this Class */
	void UnbindAllDelegates();


protected:

	/*
	@ Local WndProc called by GlobalWndProc.
	*/
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	RECT			WindowRect;

	LONG			WindowSizeX;
	LONG			WindowSizeY;

	FString			WindowTitle;
	
	HINSTANCE		hInstance;
	MSG				Msg;
	HWND			hWnd;

	HDC				hdcBackBuffer;
	HBITMAP			hbmpBackBuffer;
};

END_SODA