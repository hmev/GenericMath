#pragma once

#include <Config.h>
#include <Basic/Vector.hpp>

NameSpace_Math_Begin

namespace R3
{
	template <typename T>
	using Point3 = Vec3<T>;

	typedef Point3<float> Point3f;
	typedef Point3<double> Point3d;

	template <typename T>
	struct Polar3 : public Vector<T, 3>
	{
	public:
		inline T& theta() { return data[0]; }
		inline T& phi() { return data[1]; }
		inline T& r() { return data[2]; }
		inline T theta() const { return data[0]; }
		inline T phi() const { return data[1]; }
		inline T r() const { return data[2]; }

	public:
		inline T& x() = delete;
		inline T& y() = delete;
		inline T& z() = delete;
		inline T x() const = delete;
		inline T y() const = delete;
		inline T z() const = delete;
	};



	struct Segment;
	//struct Line;
	struct Surface;
	struct Curve;
	struct Sphere;

	template <typename T>
	struct Line
	{


	};

	template <typename T>
	struct Plane
	{
	public:
		T a, b, c, d; // ax + by + cz + d = 0;

		Plane()
			Plane(T _a, T _b, T _c, T _d) : a(_a), b(_b), c(_c), d(_d);

		Plane& fromPoints(Vec3<T> v1, Vec3<T> v2, Vec3<T> v3);

		Plane& normalize() { a /= d; b /= d; c /= d; }

	public:


	};

	template <typename T>
	T distance(const Vec3<T>& point, const Plane<T>& plane)
	{
		return (plane.a * point.x() + plane.b * point.y() + plane.c * point.z() + plane.d) / sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
	}

	template <typename T>
	bool parallel(const Line<T>&, const Plane<T>&);

	template <typename T>
	Nullable<Vec3<T>> intersect(const Line<T>&, const Plane<T>&);

	template <typename T>
	bool parallel(const Plane<T>&, const Plane<T>&);

	template <typename T>
	Nullable<Line<T>> intersect(const Plane<T>&, const Plane<T>&);

	template <typename T>
	T angle(const Plane<T>& plane1, const Plane<T>& plane2)
	{
		return std::acos((plane1.a * plane2.a + plane1.b * plane2.b + plane1.c * plane2.c) / (sqrt(plane1.a*plane1.a + plane1.b*plane1.b + plane1.c*plane1.c)*sqrt(plane2.a*plane2.a + plane2.b*plane2.b + plane2.c*plane2.c)));
	}

	template <typename T>
	Vec3<T> cross3(Vec3<T> v1, Vec3<T> v2)
	{
		Vec3d v;
		v[0] = v1[1] * v2[2] - v1[2] * v2[1];
		v[1] = v1[2] * v2[1] - v1[1] * v2[2];
		v[2] = v1[0] * v2[1] - v1[1] * v2[0];
		return v;
	}
}

NameSpace_Math_End