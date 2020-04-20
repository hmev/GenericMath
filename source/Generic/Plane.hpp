#pragma once
#include <Math/Math.h>
#include <Math/Basic/Vector.hpp>
#include <Math/Generic/Point.hpp>

NameSpace_Math_Begin

// Plane : R(n-1) Space in R(n)

template <typename T, int D>
struct Plane
{
protected:
	// a1 * x1 + a2 * x2 + ... + 1 = 0;
	Vector<T, D> param;	

public:
	Plane() {}
	Plane(const std::initialize_list<T>& list)
	{
		assert(list.size() == N);	// TODO
		int i = 0;
		for (auto iter = list.begin(); iter != list.end(); iter++) { param[i++] = *iter; }
	}
	Vector<T, D> nvec() const 
	{
		return param;
	}
};

template <typename T, int D>
T distance(const Vector<T, D>& point, const Plane<T, D>& plane)
{
	return (inner(plane.nvec(), point) + 1) / norm(plane.nvec());
}

template <typename T, int D>
T angle(const Plane<T, D>& plane1, const Plane<T, D>& plane2)
{
	return angle(plane1.nvec(), plane2.nvec());
}

NameSpace_Math_End