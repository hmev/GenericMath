#pragma once
#include <cmath>
#include <complex.h>

#include "Math/Math.h"
#include "Math/Basic/Complex.hpp"

NameSpace_Math_Begin

#define ReturnForSinous(value) \
	if (Equal(value, 0)) \
	return 0.0; \
	else if (Equal(value, 1.0)) \
	return 1.0; \
	else if (Equal(value, -1.0)) \
	return -1.0; \
	else return value; 

template <typename T> 
T sin(T rad)
{
	T value = std::sin(rad);
	ReturnForSinous(value);
}

template <typename T>
T sindeg(T deg)
{
	return sin(DEG2RAD(deg));
}

template <typename T>
T cos(T rad)
{
	T value = std::cos(rad);
	ReturnForSinous(value);
}

template <typename T>
T cosdeg(T deg)
{
	return cos(DEG2RAD(deg));
}

template <typename T>
T tan(T rad)
{
	T value = std::tan(rad);
	ReturnForSinous(value);
}

template <typename T>
T tandeg(T deg)
{
	return tan(DEG2RAD(deg));
}

//template <typename T>
//Complex<typename FloatPromoter<T>::type> csin(Complex<T> z)
//{
//	return z;
//}
//
//template <typename T>
//Complex<T> ccos(Complex<T> z)
//{
//	return z;
//}

#undef ReturnForSinous

NameSpace_Math_End