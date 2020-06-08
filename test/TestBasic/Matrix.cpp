#include <gtest/gtest.h>
#include <Basic/Matrix.hpp>
#include <Basic/Complex.hpp>
#include <iostream>

NameSpace_Math_Begin

template struct Matrix<int, 2, 2>;
template struct Matrix<int, 3, 3>;
template struct Matrix<long, 2, 2>;
template struct Matrix<long, 3, 3>;
template struct Matrix<float, 2, 2>;
template struct Matrix<float, 3, 3>;
template struct Matrix<double, 2, 2>;
template struct Matrix<double, 3, 3>;
template struct Matrix<Complex<int>, 2, 2>;
template struct Matrix<Complex<int>, 3, 3>;
template struct Matrix<Complex<long>, 2, 2>;
template struct Matrix<Complex<long>, 3, 3>;
template struct Matrix<Complex<double>, 2, 2>;
template struct Matrix<Complex<double>, 3, 3>;
template struct Matrix<Complex<double>, 2, 2>;
template struct Matrix<Complex<double>, 3, 3>;

TEST(Matrix, Initialization)
{
	/// m1 = 0 1 2
	///      3 4 5
	Matrix<double, 2, 3> m1({
		{0, 1, 2}, 
		{3, 4, 5},
	});
	EXPECT_EQ(m1(1, 0), 3);
	EXPECT_EQ(m1(1, 1), 4);

	Matrix<double, 2, 3> m2 = {
		{0, 1, 2}, 
		{3, 4, 5},		
	};
	EXPECT_EQ(m2(1, 0), 3);
	EXPECT_EQ(m2(1, 1), 4);

	Matrix<double, 2, 3> m3 = {
		{0, 1, 2}, 
		{3, 4, 6}, 		
	};

	EXPECT_EQ(m1, m2);
	EXPECT_NE(m1, m3);

	Matrix<double, 3, 2> m4({
		{0, 3}, 
		{1, 4},
		{2, 5}
	});

	EXPECT_EQ(transpose(m1), m4);
}

TEST(Matrix, Common)
{
	Matrix<double, 2, 3> left = {
		{0, 1, 2}, 
		{3, 4, 5},
	};

	Matrix<double, 3, 3> m = {
		{1, 1, 0}, 
		{0, 1, 0}, 
		{0, 0, 1}
	};

	Matrix<double, 2, 3> leftrst = {
		{0, 1, 2}, 
		{3, 7, 5}, 		
	};

	Matrix<double, 3, 2> right = {
		{0, 1},
		{2, 3},
		{4, 5}
	};

	Matrix<double, 3, 2> rightrst = {
		{2, 4},
		{2, 3},
		{4, 5}
	};
		
	EXPECT_EQ(left * m, leftrst);
	EXPECT_EQ(m * right, rightrst);

	auto m2 = left;
	EXPECT_EQ(left.rmul(m), leftrst);

	auto m3 = right;
	EXPECT_EQ(right.lmul(m), rightrst);
}


NameSpace_Math_End