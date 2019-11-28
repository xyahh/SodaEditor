// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once

BEGIN_SODA

using SodaColor		= Gdiplus::Color;
using SodaBitmap	= Gdiplus::Bitmap;
using SodaGraphics	= Gdiplus::Graphics;
using SodaPen		= Gdiplus::Pen;
using SodaSmoothing = Gdiplus::SmoothingMode;

/* RAII for GdiPlus Startup
@ Handles Lifetime of GdiPlus functionality */
class SodaGraphicsStartup
{
public:

	SodaGraphicsStartup()
	{
		Gdiplus::GdiplusStartupInput StartupInput;
		Gdiplus::GdiplusStartup(&SodaGraphicsToken, &StartupInput, NULL);
	}

	void Destroy()
	{
		Gdiplus::GdiplusShutdown(SodaGraphicsToken);
	}	~SodaGraphicsStartup()


	{
		Destroy();
	}
	
private:
	ULONG_PTR		SodaGraphicsToken;
};

END_SODA