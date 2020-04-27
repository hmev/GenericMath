#pragma once

#include <Config.h>

NameSpace_Math_Begin

// Real Field

template <typename T>
struct Trait
{
	static const unsigned int level = INT_MAX;
	static bool norm(T v) { return v; }
	static bool equal(T v1, T v2) { return v1 == v2; }
};

template <>
struct Trait < int >
{
	static const unsigned int level = 0;
	static bool norm(int v) { return v; }
	static bool equal(int v1, int v2) { return v1 == v2; }
};

template <>
struct Trait < long >
{
	static const unsigned int level = 1;
	static bool norm(long v) { return v; }
	static bool equal(long v1, long v2) { return v1 == v2; }
};

template <>
struct Trait < float >
{
	static const unsigned int level = 2;
	static bool norm(float v) { return v; }
	static bool equal(float v1, float v2) { return Equal(v1, v2); }
};

template <>
struct Trait < double >
{
	static const unsigned int level = 3;
	static bool norm(double v) { return v; }
	static bool equal(double v1, double v2) { return Equal(v1, v2); }
};

template <int l>
struct TraitSelector;

template <>
struct TraitSelector < 0 >
{
	typedef int type;
};

template <>
struct TraitSelector < 1 >
{
	typedef long type;
};

template <>
struct TraitSelector < 2 >
{
	typedef float type;
};

template <>
struct TraitSelector < 3 >
{
	typedef double type;
};

template <typename T1, typename T2>
struct TraitPromoter
{
	static const unsigned int promoted_level = Trait<T1>::level | Trait<T2>::level;
	typedef typename TraitSelector<promoted_level>::type promoted;
};

template <typename T>
struct FloatPromoter
{
	typedef typename TraitPromoter<T, float>::promoted type;
};

NameSpace_Math_End