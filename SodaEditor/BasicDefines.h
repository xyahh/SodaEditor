// Copyright 2019, Juan Marcelo Portillo. All Rights Reserved.


#pragma once


/* 
Some shortcuts that makes code more readable by reducing
the namespace indentation.
*/
#define BEGIN_SODA namespace Soda {
#define END_SODA }

#define USE_SODA using namespace Soda
#define SODA Soda::

#define STD std::


/*
@ Check if a class is child of a certain class
@ Explicit -> can only be child and NOT parent (e.g. EXPLICIT_CHILD_OF_TEMPLATE(A, A) will return false)
@ Implicit -> the class to test can also be the Base (e.g. IMPLICIT_CHILD_OF_TEMPLATE(A, A) will return true)
*/
#define EXPLICIT_CHILD_OF_TEMPLATE(T, Base, ...) template<class T, typename STD enable_if<STD is_base_of<Base, T>::value && !STD is_same<Base, T>::value, bool>::type = 0, __VA_ARGS__>
#define IMPLICIT_CHILD_OF_TEMPLATE(T, Base, ...) template<class T, typename STD enable_if<STD is_base_of<Base, T>::value, bool>::type = 0, __VA_ARGS__>

/*

MORE DEFINITIONS

@ "SODA_DEBUG_MODE" -> Puts Debugging Mode on (Console is allocated and SODA_LOGs print to Console)
@ "SODA_64"			-> Machine is in x64 Environment, so TQueue and Multithreading features can be used with no problem

*/