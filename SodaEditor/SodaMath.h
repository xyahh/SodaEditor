// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include <DirectXPackedVector.h>
#include <DirectXMath.h>
#include <float.h>

#define DX DirectX:: 

#define MathCallConv XM_CALLCONV

BEGIN_SODA

/*
@ Checks if fValue is close to Zero
*/
inline bool Zero(float value)
{
	return  fabsf(value) < FLT_EPSILON;
}

/*
@ Clamps a value in the Range lowest <= n <= highest
*/
template<class T>
inline void Clamp(T lowest, T * n, T highest)
{
	*n = max(lowest, min(*n, highest));
}

/*
@ Checks if low <= n <= high
*/
inline bool InRange(float low, float n, float high)
{
	return (n >= low) && (n <= high);
}

using FVector = DX XMVECTOR;

using Float2 = DX XMFLOAT2;
using Float3 = DX XMFLOAT3;
using Float4 = DX XMFLOAT4;

using Uint2	= DX XMUINT2;

/*
Adding Convenience Data Types to
avoid having to remember everytime how XMVECTORs
should be passed.
*/

using FVectorParam1 = DX FXMVECTOR;
using FVectorParam2 = DX FXMVECTOR;
using FVectorParam3 = DX FXMVECTOR;
using FVectorParam4 = DX GXMVECTOR;
using FVectorParam5 = DX HXMVECTOR;
using FVectorParam6 = DX HXMVECTOR;
using FVectorParamX = DX CXMVECTOR;

/* Gets X component of the Vector */
inline float MathCallConv GetX(FVectorParam1 v)
{
	return DX XMVectorGetX(v);
}

/* Gets Y component of the Vector */
inline float MathCallConv GetY(FVectorParam1 v)
{
	return DX XMVectorGetY(v);
}

/* Gets Z component of the Vector */
inline float MathCallConv GetZ(FVectorParam1 v)
{
	return DX XMVectorGetZ(v);
}

/* Gets W component of the Vector */
inline float MathCallConv GetW(FVectorParam1 v)
{
	return DX XMVectorGetW(v);
}

/* Sets X component of the Vector */
inline void MathCallConv SetX(FVector* out, float value)
{
	*out = DX XMVectorSetX(*out, value);
}

/* Sets Y component of the Vector */
inline void MathCallConv SetY(FVector* out, float value)
{
	*out = DX XMVectorSetY(*out, value);
}

/* Sets Z component of the Vector */
inline void MathCallConv SetZ(FVector* out, float value)
{
	*out = DX XMVectorSetZ(*out, value);
}

/* Sets W component of the Vector */
inline void MathCallConv SetW(FVector* out, float value)
{
	*out = DX XMVectorSetW(*out, value);
}

/* Returns the Zero Vector {0.f, 0.f, 0.f, 0.f} */
inline FVector MathCallConv VectorZero()
{
	return DX XMVectorZero();
}

/* Returns a Vector of Ones {1.f, 1.f, 1.f, 1.f} */
inline FVector MathCallConv VectorOne()
{
	return DX XMVectorSplatOne();
}

/* Takes every component and makes it absolute { abs(x), abs(y), abs(z), abs(w) }*/
inline FVector MathCallConv Abs(FVectorParam1 v)
{
	return DX XMVectorAbs(v);
}

/* OPERATORS */

/* Scales the Vector by a float factor { x*scale, y*scale, z*scale, w*scale } */
inline FVector MathCallConv Scale(FVectorParam1 v, float scale)
{
	return DX XMVectorScale(v, scale);
}

/* Adds two vectors by component 
   Result.x = v1.x + v2.x
   Result.y = v1.y + v2.y
   Result.z = v1.z + v2.z
   Result.w = v1.w + v2.w
*/
inline FVector MathCallConv Add(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorAdd(v1, v2);
}

/* Subtracts two vectors by component
   Result.x = v1.x - v2.x
   Result.y = v1.y - v2.y
   Result.z = v1.z - v2.z
   Result.w = v1.w - v2.w
*/
inline FVector MathCallConv Subtract(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorSubtract(v1, v2);
}

/* Stores a Vector into Float2 (x, y) Data Struct */
inline Float2 MathCallConv StoreFloat2(FVectorParam1 v)
{
	Float2 Storage;
	DX XMStoreFloat2(&Storage, v);
	return Storage;
}

/* Stores a Vector into a Uint2 (x, y) Data Struct */
inline Uint2 MathCallConv StoreUint2(FVectorParam1 v)
{
	Uint2 Storage;
	DX XMStoreUInt2(&Storage, v);
	return Storage;
}

/* Stores a Vector into Float3 (x, y, z) Data Struct */
inline Float3 MathCallConv StoreFloat3(FVectorParam1 v)
{
	Float3 Storage;
	DX XMStoreFloat3(&Storage, v);
	return Storage;
}

/* Stores a Vector into Float4 (x, y, z, w) Data Struct */
inline Float4 MathCallConv StoreFloat4(FVectorParam1 v)
{
	Float4 Storage;
	DX XMStoreFloat4(&Storage, v);
	return Storage;
}

/* Loads a Float2 (x, y) Data Struct into a vector */
inline FVector MathCallConv LoadFloat2(const Float2& v)
{
	return DX XMLoadFloat2(&v);
}

/* Loads a Uint2 (x, y) Data Struct into a vector */
inline FVector MathCallConv LoadUint2(const Uint2& v)
{
	return DX XMLoadUInt2(&v);
}

/* Loads a Float3 (x, y) Data Struct into a vector */
inline FVector MathCallConv LoadFloat3(const Float3& v)
{
	return DX XMLoadFloat3(&v);
}

/* Loads a Float4 (x, y) Data Struct into a vector */
inline FVector MathCallConv LoadFloat4(const Float4& v)
{
	return DX XMLoadFloat4(&v);
}

/* Performs 2D Dot Product */
inline float MathCallConv DotV2(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorGetX(DX XMVector2Dot(v1, v2));
}

/* Performs 3D Dot Product */
inline float MathCallConv DotV3(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorGetX(DX XMVector3Dot(v1, v2));
}

/* Performs 2D Cross Product */
inline FVector MathCallConv CrossV2(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVector2Cross(v1, v2);
}

/* Performs 3D Cross Product */
inline FVector MathCallConv CrossV3(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVector3Cross(v1, v2);
}

/* Gets the Distance of a 2D Vector */
inline float MathCallConv DistanceV2(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorGetX(DX XMVector2Length(DX XMVectorSubtract(v2, v1)));
}

/* Gets the Distance of a 3D Vector */
inline float MathCallConv DistanceV3(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorGetX(DX XMVector3Length(DX XMVectorSubtract(v2, v1)));
}

/* Gets the Squared Distance of a 2D Vector */
inline float MathCallConv DistanceSqV2(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorGetX(DX XMVector2LengthSq(DX XMVectorSubtract(v2, v1)));
}

/* Gets the Squared Distance of a 3D Vector */
inline float MathCallConv DistanceSqV3(FVectorParam1 v1, FVectorParam2 v2)
{
	return DX XMVectorGetX(DX XMVector3LengthSq(DX XMVectorSubtract(v2, v1)));
}

END_SODA