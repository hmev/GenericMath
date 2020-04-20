#pragma once


template <typename T, int D>
struct Quadratic
{
protected:
	// a1^2 * (x1-c0)^2 + a2^2 * (x1-c0)^2 + ... + 1 = 0;
	Vector<T, D> param;
	Vector<T, D> center;
	Vector<int, D> signal; // +1 or -1;



};
