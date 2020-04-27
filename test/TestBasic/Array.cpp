#include <gtest/gtest.h>
#include <Basic/Array.hpp>
#include <Basic/Complex.hpp>

NameSpace_Math_Begin

template struct Array<int>;
template struct Array<long>;
template struct Array<float>;
template struct Array<double>;
template struct Array<Complexi>;
template struct Array<Complexf>;
template struct Array<Complexd>;

TEST(Array, Common)
{
	Array<double> arr(Scale({ 3 }), {1, 2, 3});
	Array<double> arr2(Scale({ 2, 3 }), {1,2,3,4,5,6 });
}

NameSpace_Math_End