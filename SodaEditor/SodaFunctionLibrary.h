#pragma once

BEGIN_SODA

template<typename GraphicsObj>
inline bool SafeRelease(GraphicsObj& obj)
{
	if (!obj) return false;
	DeleteObject(obj);
	obj = NULL;
	return true;
}
/*
@ Clamps a value in the Range lowest <= n <= highest
*/
template<class T>
inline void Clamp(T lowest, T * n, T highest)
{
	*n = max(lowest, min(*n, highest));
}



END_SODA