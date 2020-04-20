#pragma once

#include <Math/Math.h>
#include <Math/Generic/ParametricFunction.hpp>

NameSpace_Math_Begin

template <typename T, int D>
struct Curve
{
public:
	Curve(ParametricFunction<T>[D - 1] paramFunc);
	bool validate();

protected:
	ParametricFunction<T>[D - 1] paramFunc;
};

NameSpace_Math_End