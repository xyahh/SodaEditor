// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include <string>

BEGIN_SODA

#ifdef UNICODE

using FChar = wchar_t;
using FParentString = STD wstring;
#define SODA_PRINT(Msg, ...)	wprintf(Msg, __VA_ARGS__)

#else

using FChar = char;
using FParentString = STD string;
#define SODA_PRINT(Msg, ...)	printf(Msg, __VA_ARGS__)

#endif


#ifdef SODA_DEBUG
/*
@ In Debug Mode, Printing to Console is available
@ In Release Mode, SODA LOG will not do anything.
*/
#define SODA_LOG(Msg, ...)		SODA_PRINT(TEXT(Msg), __VA_ARGS__)
#else
#define SODA_LOG(Msg, ...)		
#endif

/*
@ FString helps to wrap around the issue with running the program
@ with Unicode or with Multibyte Char set.
@ FString is Child of either std::wstring(Unicode) or std::string(Multibyte)
@ and adds some extra functionality for convenience!
*/
class FString : public FParentString
{
public:
	
	FString() {}

	/* ParentString operators used so that we can initialize like we do with std::string/std::wstring */
	FString(const FParentString& Str) : FParentString(Str) {}
	FString(FParentString&& Str) noexcept : FParentString(STD move(Str)) {}

	FString(const STD initializer_list<FChar>& Init) : FParentString(Init) {}
	FString(STD initializer_list<FChar>&& Init) noexcept : FParentString(STD move(Init)) {}

	template<class Iter>
	FString(Iter begin_, Iter end_) : FParentString(begin_, end_) {}

	FString(const FChar* Str) : FParentString(Str) {}

	~FString() {}

	const FChar* operator*() const
	{
		return this->c_str();
	}

	/*
	@ Converts data (e.g. int, double, float, etc) to the Parent's String
	@ depending on whether we use Unicode or Multibyte
	*/
	template<class T>
	static FString ToString(const T& Data)
	{
#ifdef UNICODE
		return STD to_wstring(Data);
#else
		return STD to_string(Data);
#endif
	}
};

END_SODA