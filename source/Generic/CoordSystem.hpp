#pragma once

#include "Math/Math.h"
#include "Math/Basic/Vector.hpp"

NameSpace_Math_Begin

template <int D>
struct CoordSystem 
{
	template <typename T>
	using ParamType = Vector < T, D >;
	template <typename T>
	using PointType = Vector < T, D >;
};

template <int D>
struct Cartesian : public CoordSystem<D>
{
	template <typename T>
	using ParamType = Vector < T, D >;
	template <typename T>
	using PointType = Vector < T, D >;

	static Vector<int, D> axis(int n) { Vector<int, D> v; v[n] = 1; return v; }
	template <typename T>
	static PointType<T> calc(const ParamType<T>& param) { return param; };
	template <typename T>
	static ParamType<T> proj(const PointType<T>& point) { return point; };
};

template <int D>
Vector<int, D> xAxis() { return Cartesian::axis(0); }
template <int D>
Vector<int, D> yAxis() { return Cartesian::axis(1); }
template <int D>
Vector<int, D> zAxis() { return Cartesian::axis(2); }

typedef Cartesian<2> Cart2;
typedef Cartesian<3> Cart3;

template <int D>
struct Sphere;

template <>
struct Sphere<2> : public CoordSystem<2>
{
	template <typename T>
	struct Polar2 : public Vector<T, 2>
	{
	public:
		typedef Vector<T, 2> base_type;

		inline T& r() { return base_type::data[0]; }
		inline T& phi() { return base_type::data[1]; }
		inline T r() const { return base_type::data[0]; }
		inline T phi() const { return base_type::data[1]; }

	public:
		inline T& x() = delete;
		inline T& y() = delete;
		inline T& z() = delete;
		inline T x() const = delete;
		inline T y() const = delete;
		inline T z() const = delete;
	};

	template <typename T>
	using ParamType = Vector < T, 2 >;
	template <typename T>
	using PointType = Vector < T, 2 >;

	template <typename T>
	static inline PointType<T> calc(const ParamType<T>& param /* r, phi */)
	{
		return PointType<T>({param[0] * cos(param[1]), param[0] * sin(param[1])});
	}

	template <typename T>
	static inline ParamType<T> proj(const PointType<T>& point)
	{
		ParamType<T> p;
		T l1 = point.x() * point.x() + point.y() * point.y();

		p[0] /* r */ = std::sqrt(l1 + point.z() * point.z());
		p[1] /* phi */ = std::atan2(point.y(), point.x());

		if (_Zero(p[1]) && point.y() > 0)
			p[1] = 0;
		if (point.y() < 0)
			p[1] += PI * 2.0;

		return p;
	}
};

template <typename T>
inline Vec2<T> polar2cart(T phi, T radius = 1.0)
{
	Sphere<2>::calc(Vec2<T>(radius, phi));
}

template <typename T>
inline Vec2<T> polar2cart_d(T phi, T radius = 1.0)
{
	return polar2cart(DEG2RAD(phi));
}

template <>
struct Sphere<3> : public CoordSystem<3>
{
	template <typename T>
	struct Polar3 : public Vector<T, 3>
	{
	public:
		typedef Vector<T, 3> base_type;

		inline T& r() { return base_type::data[0]; }
		inline T& theta() { return base_type::data[1]; }
		inline T& phi() { return base_type::data[2]; }
		inline T r() const { return base_type::data[0]; }
		inline T theta() const { return base_type::data[1]; }
		inline T phi() const { return base_type::data[2]; }

	public:
		inline T& x() = delete;
		inline T& y() = delete;
		inline T& z() = delete;
		inline T x() const = delete;
		inline T y() const = delete;
		inline T z() const = delete;
	};

	template <typename T>
	using ParamType = Vector < T, 3 >;
	template <typename T>
	using PointType = Vector < T, 3 >;

	template <typename T>
	static inline PointType<T> calc(const ParamType<T>& param)
	{
		double costh = cos(param[1]/*theta*/);
		double sinth = sin(param[1]/*theta*/);
		return param[0]/*r*/ * Vec3<T>(sinth * cos(param[2]/*phi*/), sinth * sin(param[2]/*phi*/), costh);
	}

	template <typename T>
	static inline ParamType<T> proj(const PointType<T>& point)
	{
		ParamType<T> p;
		T l1 = point.x() * point.x() + point.y() * point.y();

		p[0] /* r */ = std::sqrt(l1 + point.z() * point.z());
		p[1] /* theta */ = std::atan2(point.z(), std::sqrt(l1));
		p[2] /* phi */ = std::atan2(point.y(), point.x());

		if (_Zero(p[2]) && point.y() > 0)
			p[2] = 0;
		if (point.y() < 0)
			p[2] += PI * 2.0;
		
		return p;
	}
};

typedef Sphere<2> Sphere2;
typedef Sphere<3> Sphere3;


template <typename T>
inline Vec3<T> sph2cart(T theta, T phi, T radius = 1.0)
{
	return Sphere<3>::calc(Vec3<T>(radius, theta, phi));
}

template <typename T>
inline Vec3<T> sph2cart_d(T theta, T phi, T radius = 1.0)
{
	return sph2cart(DEG2RAD(theta), DEG2RAD(phi), radius);
}

template <typename T>
inline Vec3<T> cart2sph(const Vec3<T>& point)
{
	return Sphere<3>::proj(point);
}

template <typename T>
inline Vec3<T> cart2sph_d(const Vec3<T>& point)
{
	return Sphere<3>::proj(point).scale(1.0, RAD2DEG(1.0), RAD2DEG(1.0));
}

struct Cylinder3 : public CoordSystem<3>
{
	template <typename T>
	static inline PointType<T> calc(const ParamType<T>& param)
	{
		return PointType<T>({param[0] * cos(param[1]), param[0] * sin(param[1]), param[2]});
	}
	template <typename T>
	static inline ParamType<T> proj(const PointType<T>& point)
	{
		ParamType<T> p;
		T l1 = point.x() * point.x() + point.y() * point.y();

		p[0] /* r */ = std::sqrt(l1 + point.z() * point.z());
		p[1] /* phi */ = std::atan2(point.y(), point.x());

		if (_Zero(p[1]) && point.y() > 0)
			p[1] = 0;
		if (point.y() < 0)
			p[1] += PI * 2.0;

		p[2] = point.z();

		return p;
	}
};

template <typename T>
inline Vec3<T> cyl2cart(const Vec3<T>& polar)
{
	return Cylinder3::calc(polar);
}

template <typename T>
inline Vec3<T> cyl2cart_d(const Vec3<T>& polar)
{
	return Cylinder3::calc(scale(polar, Vec3<T>(1, DEG2RAD(1), 1)));
}

template <typename T>
inline Vec3<T> cart2cyl(const Vec3<T>& point)
{
	return Cylinder3::proj(point);
}

template <typename T>
inline Vec3<T> cart2cyl_d(const Vec3<T>& point)
{
	return scale(Cylinder3::proj(point), Vec3<T>(1, RAD2DEG(1), 1));
}

NameSpace_Math_End