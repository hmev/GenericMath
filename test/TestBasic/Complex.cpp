#include <gtest/gtest.h>
#include <Basic/Complex.hpp>

NameSpace_Math_Begin

template struct Complex<int>;
template struct Complex<long>;
template struct Complex<float>;
template struct Complex<double>;

TEST(Complex, Common)
{
    Complex<double> c1(1, 1);
    Complex<double> c2 = 1.0 + I(-1.0);

	EXPECT_EQ(c1 + c2, 2);
	EXPECT_EQ(c1 - c2, I(2));
	EXPECT_EQ(c1 * c2, 2);
	EXPECT_EQ(c1 / c2, I(1));

	EXPECT_FLOAT_EQ(c1.mod(), sqrt(2.0));
	EXPECT_FLOAT_EQ(c1.angle(), DEG2RAD(45));
	EXPECT_FLOAT_EQ(c1.angleDeg(), 45);
	EXPECT_EQ(-c1, -1 + I(-1));

	EXPECT_EQ(c1, c1);
	EXPECT_NE(c1, c2);

	Complex<double> c3 = 1.0;
	c3 += I(1.0);
	EXPECT_EQ(c1, c3);
	c3 -= I(2.0);
	EXPECT_EQ(c2, c3);
	c3 *= 2.0;
	EXPECT_EQ(c3, c2 * 2.0);
	c3 /= 2.0;
	EXPECT_EQ(c3, c2);
}

NameSpace_Math_End