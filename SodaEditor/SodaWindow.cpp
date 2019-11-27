// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#include "stdafx.h"
#include "SodaWindow.h"

USE_SODA;

SodaWindow::SodaWindow(const FString & WindowTitle, int Width, int Height)
{

}

SodaWindow::~SodaWindow()
{

}

LRESULT SodaWindow::GlobalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

bool SodaWindow::ProcessMessage()
{
	return false;
}

void SodaWindow::SwapBuffers()
{
}

void SodaWindow::StartWindow()
{
}

LRESULT SodaWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
