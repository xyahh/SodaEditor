// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaWindow.h"

#ifdef SODA_DEBUG
#include <fcntl.h>
#include <io.h>
#endif


USE_SODA;

SodaWindow::SodaWindow(const FString & _WindowTitle, int CenterOffsetX, int CenterOffsetY, int Width, int Height)
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

	//Standard Window Initialization
	WindowTitle = _WindowTitle;
	WindowSizeX = Width;
	WindowSizeY = Height;

	RECT WindowRect{ 0, 0, WindowSizeX, WindowSizeY };

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

	/* Spawn the Window at the Desktop's Center */
	POINT WindowDefPos
	{
		(ScreenSize.right - WindowRect.right) / 2 ,
		(ScreenSize.bottom - WindowRect.bottom) / 2
	};

	hWnd = CreateWindowEx(
		dwExStyle, lpszClass, *WindowTitle,
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		WindowDefPos.x + CenterOffsetX, //Adding Offset to Support Multiple Windows being opened in different Positions
		WindowDefPos.y + CenterOffsetY,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL, NULL, hInstance, NULL);

	//Create Back Buffer on Window Init
	CreateBackBuffer();

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
	
}

SodaWindow::~SodaWindow()
{
	ReleaseBackBuffer();

	DestroyWindow(hWnd);
	UnregisterClass(*WindowTitle, hInstance);
	hdcBackBuffer = NULL;
	hWnd = NULL;
	hInstance = NULL;
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

void SodaWindow::GetWindowSize(LONG * X, LONG * Y)
{
	*X = WindowSizeX;
	*Y = WindowSizeY;
}

void SodaWindow::CreateBackBuffer()
{
	ReleaseBackBuffer();
	hdcBackBuffer = CreateCompatibleDC(nullptr);

	HDC hdc = GetDC(hWnd);

	hbmpBackBuffer = CreateCompatibleBitmap(hdc,
		WindowSizeX,
		WindowSizeY);

	SelectObject(hdcBackBuffer, hbmpBackBuffer);

	ReleaseDC(hWnd, hdc);
}

void SodaWindow::SwapBuffers()
{
	HDC hdc = GetDC(hWnd);
	RECT ClientRect;
	GetClientRect(hWnd, &ClientRect);

	BitBlt(hdc,
		ClientRect.left, //x
		ClientRect.top,  //y
		(ClientRect.right - ClientRect.left), //width
		(ClientRect.bottom - ClientRect.top), //height
		hdcBackBuffer, 
		ClientRect.left, 
		ClientRect.top,
		SRCCOPY);
	ReleaseDC(hWnd, hdc);
}

void SodaWindow::ReleaseBackBuffer()
{
	SafeRelease(hbmpBackBuffer);
	SafeRelease(hdcBackBuffer);
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
	return SodaGraphics::FromHDC(hdcBackBuffer);
}

void SodaWindow::GetCursorPosition(int * outX, int * outY) const
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	
	*outX = static_cast<int>(p.x);
	*outY = static_cast<int>(p.y);

}

void SodaWindow::UnbindAllDelegates()
{
	OnMouseProc.UnbindAll();
	OnWindowResized.UnbindAll();
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

	/* Update Window Size Vars everytime it is Resized */
	case WM_SIZE:
	{
		WindowSizeX = LOWORD(lParam);
		WindowSizeY = HIWORD(lParam);

		//Resize the Buffers on Release
		ReleaseBackBuffer();
		CreateBackBuffer();

		OnWindowResized.Call(WindowSizeX, WindowSizeY);
		return FALSE;
	}

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		OnMouseProc.Call(xPos, yPos, wParam, (uMsg == WM_LBUTTONDOWN) || (uMsg == WM_RBUTTONDOWN) || (uMsg == WM_MOUSEMOVE));
		return FALSE;
	}
	case  WM_ERASEBKGND:
		return FALSE;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
