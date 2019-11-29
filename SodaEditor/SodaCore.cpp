#include "stdafx.h"
#include "SodaCore.h"

#ifdef SODA_DEBUG
#include <fcntl.h>
#include <io.h>
#endif


USE_SODA;

SodaCore::SodaCore()
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

	Gdiplus::GdiplusStartupInput StartupInput;
	Gdiplus::GdiplusStartup(&SodaGraphicsToken, &StartupInput, NULL);
}

void SodaCore::Destroy()
{
	Gdiplus::GdiplusShutdown(SodaGraphicsToken);
}

SodaCore::~SodaCore()
{
	Destroy();
}
