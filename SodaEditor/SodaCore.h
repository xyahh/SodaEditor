#pragma once

BEGIN_SODA

/* RAII for GdiPlus Startup & other Functionality like Debugging
@ Handles Lifetime of GdiPlus functionality */
class SodaCore
{
public:

	SodaCore();

	void Destroy();

	~SodaCore();

private:
	ULONG_PTR		SodaGraphicsToken;
};
END_SODA