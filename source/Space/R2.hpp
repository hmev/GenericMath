#pragma once

#include "Math/Math.h"
#include "Math/Basic/Vector.hpp"

NameSpace_Math_Begin

namespace R2
{
	template <typename T>
	using Point2 = Vec2<T>;

	typedef Point2<float> Point2f;
	typedef Point2<double> Point2d;

	template <typename T>
	T angle(Vec2<T> v)
	{
		// (-180, 180] ~ (-pi, pi]
		return atan2(v[1], v[0]);
	}
	template <typename T>
	T cross2(Vec2<T> v1, Vec2<T> v2)
	{
		return (v1[0] * v2[1] - v1[1] * v2[0]);
	}
	template <typename T>
	T norm(Vec2<T> v)
	{
		return sqrt(v[0] * v[0] + v[1] * v[1]);
	}
	template <typename T>
	T inner(Vec2<T> v1, Vec2<T> v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1];
	}
	template <typename T>
	Vec2<T> normalize(Vec2<T> v)
	{
		return v / inner(v, v);
	}
	template <typename T>
	T distance(Point2<T> p1, Point2<T> p2)
	{
		return norm(p1 - p2);
	}
	template <typename T>
	bool onLine(Point2<T> p1, Point2<T> p2, Point2<T> p3)
	{
		return _Zero(cross2(p1 - p2, p1 - p3));
	}

	//======================================================

	template <typename T>
	struct Segment;
	template <typename T>
	struct Line;
	template <typename T>
	struct Circle;
	template <typename T>
	struct Section;
	template <typename T>
	struct Curve;

	template <typename T /* float, double */>
	struct Segment
	{
		enum { TheSame, Parallel, Intersected, NonIntersected, Connected, Overlapped };

		Point2<T> p1, p2;

		Segment() {}
		Segment(Point2<T> _p1, Point2<T> _p2) : p1(_p1), p2(_p2) {}

		// !! Not Safe !!
		T* getX(T y) const
		{
			T x = Line<T>(*this).getX(y);
			return (Between(x, p1.x(), p2.x()) || Between(x, p2.x(), p1.x()))
				? x : nullptr;
		}
		// !! Not Safe !!
		T* getY(T x) const
		{
			T y = Line<T>(*this).getY(x);
			return (Between(y, p1.y(), p2.y()) || Between(y, p2.y(), p1.y()))
				? y : nullptr;
		}
	};

	template <typename T /* float, double */>
	struct Line
	{
	public:
		enum Relationship { TheSame, Parallel, Intersected };

		T a, b, c; // ax + by + c = 0;

		Line() {}
		Line(T _a, T _b, T _c) : a(_a), b(_b), c(_c) {}
		Line(Segment seg) { fromSegment(seg); }

		Line<T>& fromKD(T _k, T _d) { a = _k; b = -1; c = _d; return (*this); }
		Line<T>& fromPoints(Vec2d v1, Vec2d v2) { a = v2.y() - v1.y(); b = v1.x() - v2.x(); c = v2.y()*v1.x() - v1.y()*v2.x(); return (*this); }
		Line<T>& fromSegment(Segment seg) { fromPoints(seg.p1, seg.p2); return (*this); }
		Line<T>& fromKandPoint(Vec2d dir, Point2d p) { a = dir.y(); b = -dir.x(); c = dir.x()*p.y() - dir.y()*p.x(); return (*this); }

		Line<T>& normalize() { a /= c; b /= c; c = 1; return (*this); }

	public:

		T k() const { return -a / b; }
		T disY() const { return -c / b; }
		T disX() const { return -c / a; }
		T disO() const { return std::fabs(c / std::sqrt(a*a + b * b)); }
		T angle() const { double ang = atan2(a, -b); if (Negative(ang)) ang += PI; return ang; }
		Vec2<T>  normVector() const { return Vec2<T>({ a, b }); }

		// !! Not Safe !!
		T getX(T y) const { return -(b * y + c) / a; }
		T getY(T x) const { return -(a * x + c) / b; }

	public:
		bool parallelX() const { return Equal(b, 0); }
		bool parallelY() const { return Equal(a, 0); }
	};

	template <typename T>
	Line<T> xAxis() { return Line<T>(0, 1, 0); };
	template <typename T>
	Line<T> yAxis() { return Line<T>(1, 0, 0); };

	template <typename T>
	Line<T> formLine(Vec2<T> v1, Vec2<T> v2)
	{
		Line line;
		line.fromPoints(v1, v2);
		return line;
	}
	template <typename T>
	bool onLine(Point2<T> p, Line<T> line)
	{
		return Equal(line.a * p.x() + line.b * p.y() + line.c, 0);
	}
	template <typename T>
	bool onSegment(Point2<T> p, Segment<T> seg)
	{
		if (!onLine(p, Line().fromSegment(seg))) return false;
		return Between(p.x(), seg.p1.x(), seg.p2.x())
			|| Between(p.x(), seg.p2.x(), seg.p1.x());
	}

	template <typename T>
	bool theSame(Line<T> line1, Line<T> line2)
	{
		return Equal(line1.a * line2.c, line1.c * line2.a) && Equal(line1.b * line2.c, line1.c * line2.b);
	}
	template <typename T>
	bool parallel(Line<T> line1, Line<T> line2)
	{
		if (theSame(line1, line2)) return false;
		return Equal(line1.a * line2.b - line1.b * line1.a, 0);
	}
	template <typename T>
	Point2<T>* intersect(Line<T> line1, Line<T> line2)
	{
		if (theSame(line1, line2) || parallel(line1, line2))
		{
			return nullptr;
		}

		double x = (line1.c * line2.b - line1.b * line2.c) / (line2.a * line1.b - line2.b * line1.a);
		double y = (line1.c * line2.a - line1.a * line2.c) / (line2.b * line1.a - line2.a * line1.b);

		return Point2d({ x, y });
	}

	// Operation on Segments
	template <typename T>
	bool theSame(Segment<T> seg1, Segment<T> seg2)
	{
		return seg1.p1 == seg2.p1 && seg1.p2 == seg2.p2
			|| seg1.p2 == seg2.p1 && seg1.p1 == seg2.p2;
	}
	template <typename T>
	Point2<T>* intersect(Segment<T> seg1, Segment<T> seg2)
	{
		Point2<T> ptr_point = intersect(Line().fromSegment(seg1), Line().fromSegment(seg2));
		if (ptr_point == nullptr || onSegment(ptr_point.value(), seg1))
		{
			return nullptr;
		}
		else
		{
			return ptr_point;
		}
	}
	template <typename T>
	Point2<T>* connected(Segment<T> seg1, Segment<T> seg2)
	{
		if (theSame(Line().fromSegment(seg1), Line().fromSegment(seg2)))
		{
			Segment s1 = seg1; if (!Less(s1.p1.x(), s1.p2.x())) std::swap(s1.p1, s1.p2);
			Segment s2 = seg1; if (!Less(s2.p1.x(), s2.p2.x())) std::swap(s2.p1, s2.p2);
			if (s1.p2 == s2.p1)
				return (s1.p2);
			else if (s1.p1 == s2.p2)
				return (s1.p1);
			else
				return nullptr;
		}
		else
		{
			if (seg1.p1 == seg2.p1 || seg1.p1 == seg2.p2)
				return Nullable<Point2d>(seg1.p1);
			else if (seg1.p1 == seg2.p1 || seg1.p1 == seg2.p2)
				return (seg1.p2);
			else
				return nullptr;
		}
	}
	template <typename T>
	Segment<T>* overlap(Segment<T> seg1, Segment<T> seg2)
	{
		if (!theSame(Line().fromSegment(seg1), Line().fromSegment(seg2)))
			return nullptr;
		if (!connected(seg1, seg2).isNull())
			return nullptr;

		Segment s1 = seg1; if (!Less(s1.p1.x(), s1.p2.x())) std::swap(s1.p1, s1.p2);
		Segment s2 = seg1; if (!Less(s2.p1.x(), s2.p2.x())) std::swap(s2.p1, s2.p2);

		if (Less(s1.p1.x(), s2.p1.x()) && Less(s2.p2.x(), s1.p2.x()))
		{
			return s2;
		}
		else if (Less(s2.p1.x(), s1.p1.x()) && Less(s1.p2.x(), s2.p2.x()))
		{
			return s1;
		}
		else if (Less(s2.p1.x(), s1.p2.x()) && Less(s1.p2.x(), s2.p2.x()))
		{
			return Segment(s1.p2, s2.p1);
		}
		else if (Less(s1.p1.x(), s2.p2.x()) && Less(s2.p2.x(), s1.p2.x()))
		{
			return Segment(s2.p2, s1.p1);
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T>
	struct Circle
	{
	public:
		Vec2<T> center, radius;


	};

	template <typename T>
	struct Ellipse
	{
	public:
		T a, b; // x * x / a / a  + y * y / b / b = 1;



	};

	template <typename T>
	struct Curve
	{


	};
}

NameSpace_Math_End
