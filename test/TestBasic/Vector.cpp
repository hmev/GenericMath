#include <gtest/gtest.h>
#include <Basic/Vector.hpp>
#include <Basic/Complex.hpp>

NameSpace_Math_Begin

template struct Vector<int, 2>;
template struct Vector<int, 3>;
template struct Vector<long, 2>;
template struct Vector<long, 3>;
template struct Vector<float, 2>;
template struct Vector<float, 3>;
template struct Vector<double, 2>;
template struct Vector<double, 3>;
template struct Vector<Complex<int>, 2>;
template struct Vector<Complex<int>, 3>;
template struct Vector<Complex<long>, 2>;
template struct Vector<Complex<long>, 3>;
template struct Vector<Complex<double>, 2>;
template struct Vector<Complex<double>, 3>;
template struct Vector<Complex<double>, 2>;
template struct Vector<Complex<double>, 3>;

TEST(Vector, Common)
{
	Vec3d v1({ 1, 0, 0 });
	Vec3d v2 = { 1, 1, 0 };
	EXPECT_EQ((v1 + v2), Vec3d({ 2, 1, 0 }));
	EXPECT_EQ(v1 - v2, Vec3d({ 0, -1, 0 }));
	EXPECT_EQ(v1(0), 1);
	EXPECT_EQ(v1[1], 0);
	EXPECT_EQ(v1 == v2, false);
	EXPECT_EQ(v1 != v2, true);

	Vec3d v3;
	v3 = v1;
	EXPECT_EQ(v3, v1);
	v3 += v2;
	EXPECT_EQ(v3, Vec3d({ 2, 1, 0 }));
	v3 -= v2;
	EXPECT_EQ(v3, v1);
	v3 *= 5;
	EXPECT_EQ(v3, Vec3d({ 5, 0, 0 }));
	v3 /= 5;
	EXPECT_EQ(v3, Vec3d({ 1, 0, 0 }));
}

TEST(Vector, TypePromotion)
{
	Vec3i v1({1, 0, 0});
	Vec3d v2({1, 1, 0});
	Vec3d v3 = v1 + v2;

	EXPECT_EQ(v3, Vec3d({2,1, 0}));
}


TEST(Vector, Calculation)
{

}

NameSpace_Math_End