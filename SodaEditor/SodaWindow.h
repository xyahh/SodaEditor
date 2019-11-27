// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once

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

	void StartWindow();

	void ClearScreen(const Float4& Color)
	{
		SetDCBrushColor(hDC, RGB(Color.x, Color.y, Color.z, Color.w));
		FillRect(hDC, &WindowRect, static_cast<HBRUSH>(GetStockObject(DC_BRUSH)));
	}

protected:

	/*
	@ Local WndProc called by GlobalWndProc. Can be overriden by another Child Windows
	*/
	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	RECT		WindowRect;

	FString		WindowTitle;
	Uint2		WindowSize;

	HINSTANCE	hInstance;
	MSG			Msg;
	HWND		hWnd;

	HDC			hDC;
};

END_SODA