// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaWindow.h"

#ifdef SODA_DEBUG
#include <fcntl.h>
#include <io.h>
#endif


USE_SODA;

SodaWindow::SodaWindow(const FString & _WindowTitle, int Width, int Height)
{
	//Allocate a Console and Streams for Debugging
#ifdef SODA_DEBUG
	/* DevConsole Creation Code Source: https://stackoverflow.com/a/43870739 */
	AllocConsole();
	SetConsoleTitle(TEXT("Soda Editor Console"));
	typedef struct
	{
		char* _ptr;
		int _cnt;
		char* _base;
		int _flag;
		int _file;
		int _charbuf;
		int _bufsiz;
		char* _tmpfname;
	} FILE_COMPLETE;

	*(FILE_COMPLETE*)stdout = *(FILE_COMPLETE*)_fdopen(_open_osfhandle(PtrToLong(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT), "w");
	*(FILE_COMPLETE*)stderr = *(FILE_COMPLETE*)_fdopen(_open_osfhandle(PtrToLong(GetStdHandle(STD_ERROR_HANDLE)), _O_TEXT), "w");
	*(FILE_COMPLETE*)stdin = *(FILE_COMPLETE*)_fdopen(_open_osfhandle(PtrToLong(GetStdHandle(STD_INPUT_HANDLE)), _O_TEXT), "r");
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
#endif

	//Init GDI+
	Gdiplus::GdiplusStartupInput StartupInput;
	Gdiplus::GdiplusStartup(&SodaGraphicsToken, &StartupInput, NULL);


	//Standard Window Initialization
	WindowTitle = _WindowTitle;
	WindowSize.x = Width;
	WindowSize.y = Height;

	RECT WindowRect{ 0, 0, (LONG)WindowSize.x, (LONG)WindowSize.y };

	LPCTSTR lpszClass = *WindowTitle;
	hInstance = GetModuleHandle(NULL);

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = SodaWindow::GlobalWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = lpszClass;
	RegisterClass(&wc);

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	RECT ScreenSize;
	GetWindowRect(GetDesktopWindow(), &ScreenSize);

	POINT Center
	{
		(ScreenSize.right - WindowRect.right) / 2 ,
		(ScreenSize.bottom - WindowRect.bottom) / 2
	};

	hWnd = CreateWindowEx(
		dwExStyle, lpszClass, *WindowTitle,
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		Center.x, Center.y,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL, NULL, hInstance, NULL);

	hDC = GetDC(hWnd);
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
	
}

SodaWindow::~SodaWindow()
{
	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);
	UnregisterClass(*WindowTitle, hInstance);
	hDC = NULL;
	hWnd = NULL;
	hInstance = NULL;

	if (SodaGraphicsToken)
		Gdiplus::GdiplusShutdown(SodaGraphicsToken);
}

LRESULT SodaWindow::GlobalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/* Get the Relevant Window and Call its WndProc Func */
	SodaWindow* WindowCalled = (SodaWindow*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (WindowCalled) return WindowCalled->WndProc(hWnd, uMsg, wParam, lParam);
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool SodaWindow::ProcessMessage()
{
	// Process Win Messages and Dispatch them to WndProc. 
	// If we have no Quit messages, return true
	if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
	{
		if (Msg.message == WM_QUIT)
			return false;
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return true;
}

void SodaWindow::SwapBuffers()
{
}

void SodaWindow::StartWindow()
{
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	UpdateWindow(hWnd);
}

SodaGraphics * SodaWindow::MakeGraphics()
{
	return SodaGraphics::FromHWND(hWnd);
}

void SodaWindow::GetCursorPosition(int * outX, int * outY) const
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	
	*outX = static_cast<int>(p.x);
	*outY = static_cast<int>(p.y);

}

LRESULT SodaWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return FALSE;
	}
	case WM_MOUSEMOVE:
	{
		return FALSE;
	}
	case WM_LBUTTONDOWN:
	{

		return FALSE;
	}
	case  WM_ERASEBKGND:
		return FALSE;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
