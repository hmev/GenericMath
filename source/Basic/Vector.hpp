/// COMMENT
/// \file Vector.hpp
/// \author {hmev} ({hmev@outlook.com})
/// \brief 
/// \version 0.1
/// \date 2020-04-26
/// 
/// @copyright Copyright (c) {2020}
/// 
/// 
#pragma once

#include <cmath>
#include <initializer_list>
#include <Config.h>
#include <Basic/NumTrait.hpp>
#include <Basic/Complex.hpp>

#include <iostream>

NameSpace_Math_Begin

/// 
/// \brief Tiny Vector
///
/// Vector vs std::Vector
/// Vector is for numerical storage specifically.
/// Vector is scale-fixed. It always thinks the storage is fulfilled and unextendable.
/// Vector has more functionality for linear algebra calculation.
///
/// \tparam T int, long, float, double, complex, etc.
/// \tparam N dimension of vector space.
/// 
template <typename T, int N>
struct Vector
{
protected:
	T data[N];

public:

	/// COMMENT
	/// \brief Construct a new Vector object
	/// 
	/// 
	Vector(){}
	~Vector(){}

	Vector(const Vector<T, N>& v)
	{
		for (int i = 0; i < N; i++)	{ data[i] = v[i]; }
	}
	/* Unsafe */
	Vector(const std::initializer_list<T>& list)
	{
		//assert(list.size() == N);	// TODO
		int i = 0;
		for (auto iter = list.begin(); iter != list.end(); iter++) 	{ data[i++] = *iter; }
	}	

	template <typename T2>
	operator Vector<T2, N>()
	{
		Vector<T2, N> v;
		for (int i = 0; i < N; i++) { v[i] = T2(data[i]); }
		return v;
	}

	int size() { return N; }

	T& operator()(int i)
	{
		return data[i];
	}

	T operator()(int i) const
	{
		return data[i];
	}

	T& operator[](int i)
	{
		return data[i];
	}

	T operator[](int i) const
	{
		return data[i];
	}

	template <typename T2>
	bool operator== (const Vector<T2, N> v2) const
	{
		typedef typename TraitPromoter<T, T2>::promoted promoted_type;
		for (int i = 0; i < N; i++)
		{
			if (!Trait<promoted_type>::equal(promoted_type(data[i]), promoted_type(v2.data[i])))
				return false;
		}
		return true;
	}
	template <typename T2>
	bool operator!= (const Vector<T2, N> v2) const
	{
		typedef typename TraitPromoter<T, T2>::promoted promoted_type;
		for (int i = 0; i < N; i++)
		{
			if (!Trait<promoted_type>::equal(promoted_type(data[i]), promoted_type(v2.data[i])))
				return true;
		}
		return false;
	}

	template <typename T2>
	void operator= (const Vector<T2, N> v2)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] = v2.data[i];
		}
	}

	template <typename T2>
	void operator= (const std::initializer_list<T>& list)
	{
		int i = 0;
		for (auto iter = list.begin(); iter != list.end(); iter++) { data[i++] = *iter; }
	}

public : 

	template <typename T2>
	Vector<T, N>& operator+= (const Vector<T2, N> v2)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] += T(v2.data[i]);
		}
		return (*this);
	}

	template <typename T2>
	Vector<T, N>& operator-= (const Vector<T2, N> v2)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] -= T(v2.data[i]);
		}
		return (*this);
	}

	template <typename T2>
	Vector<T, N>& operator*= (const T2 a)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] *= T(a);
		}
		return (*this);
	}

	template <typename T2>
	Vector<T, N>& operator/= (const T2 a)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] /= T(a);
		}
		return (*this);
	}

public : 
	/* Unsafe */
	inline T& x() { return data[0]; }
	inline T& y() { return data[1]; }
	inline T& z() { return data[2]; }
	inline T x() const { return data[0]; }
	inline T y() const { return data[1]; }
	inline T z() const { return data[2]; }
};


// Affine Space

template <typename T1, typename T2, int N>
Vector<typename TraitPromoter<T1, T2>::promoted, N > operator+(const Vector<T1, N>& v1, const Vector<T2, N>& v2)
{
	Vector<typename TraitPromoter<T1, T2>::promoted, N> v;

	for (int i = 0; i < N; i++)
	{
		v[i] = v1[i] + v2[i];
	}

	return v;
}

template <typename T1, typename T2, int N>
Vector<typename TraitPromoter<T1, T2>::promoted, N > operator-(const Vector<T1, N>& v1, const Vector<T2, N>& v2)
{
	Vector<typename TraitPromoter<T1, T2>::promoted, N> v;

	for (int i = 0; i < N; i++)
	{
		v[i] = v1[i] - v2[i];
	}

	return v;
}

template <typename T1, typename T2, int N>
Vector<typename TraitPromoter<T1, T2>::promoted, N > operator*(const Vector<T1, N>& v, const T2& a)
{
	Vector<typename TraitPromoter<T1, T2>::promoted, N> vv;

	for (int i = 0; i < N; i++)
	{
		vv[i] = v[i] * a;
	}

	return vv;
}

template <typename T1, typename T2, int N>
Vector<typename TraitPromoter<T1, T2>::promoted, N > operator/(const Vector<T1, N>& v, const T2& a)
{
	Vector<typename TraitPromoter<T1, T2>::promoted, N> vv;

	for (int i = 0; i < N; i++)
	{
		vv[i] = v[i] / a;
	}

	return vv;
}

// Vector Space

template <typename T, int N>
typename TraitPromoter<T, float>::promoted norm(const Vector<T, N>& v)
{
	typedef TraitPromoter<T, float>::promoted T2;
	T2 value = 0;
	for (int i = 0; i < N; i++)
	{
		value += Trait<T>::norm(v[i]);
	}
	return std::sqrt(value);
}

template <typename T, int N>
Vector<typename TraitPromoter<T, float>::promoted, N> normalize(const Vector<T, N>& v)
{
	return v / norm(v);
}

template <typename T1, typename T2, int N>
typename TraitPromoter<T1, T2>::promoted inner(const Vector<T1, N>& v1, const Vector<T2, N>& v2)
{
	typename TraitPromoter<T1, T2>::promoted v = 0;

	for (int i = 0; i < N; i++)
	{
		v += v1[i] * v2[i];
	}

	return v;
}

template <typename T, int N>
Vector<typename TraitPromoter<T, float>::promoted, N> angle(const Vector<T, N>& v)
{
	typename TraitPromoter<T, float>::promoted _norm = norm(v);

	Vector<typename TraitPromoter<T, float>::promoted, N> vv;
	for (int i = 0; i < N; i++)
	{
		vv = acos(v[i], _norm);
	}
	return vv;
}

template <typename T1, typename T2, int N>
typename TraitPromoter<typename TraitPromoter<T1, T2>::promoted, float>::promoted angle(const Vector<T1, N>& v1, const Vector<T2, N>& v2)
{
	return std::acos(inner(v1, v2) / (v1.norm() * v2.norm));
}

template <typename T, int N>
Vector<T, N> scale(const Vector<T, N>& vec, const T& _scale)
{
	return vec * _scale;
}

template <typename T, int N>
Vector<T, N> scale(const Vector<T, N>& vec, const Vector<T, N>& _scale)
{
	Vector<T, N> v2;

	for (int i = 0; i < N; i++)
	{
		v2[i] = vec[i] * _scale[i];
	}
	return v2;
}


// Product Space

template <typename T, int N>
T dot(const Vector<T, N>& vec1, const Vector<T, N>& vec2)
{
	T value = 0;

	for (int i = 0; i < N; i++)
	{
		value += vec1[i] * vec2[i];
	}
	return value;
}

template <typename T, int N>
Vector<T, N> inPlaceAdd(const Vector<T, N>& vec, const Vector<T, N>& _scale)
{
	Vector<T, N> v2;

	for (int i = 0; i < N; i++)
	{
		v2[i] = vec[i] + _scale[i];
	}
	return std::move(v2);
}

template <typename T, int N>
Vector<T, N> inPlaceMul(const Vector<T, N>& vec, const Vector<T, N>& _scale)
{
	Vector<T, N> v2;

	for (int i = 0; i < N; i++)
	{
		v2[i] = vec[i] * _scale[i];
	}
	return std::move(v2);
}

template <typename T, int N>
T reduceSum(const Vector<T, N>& vec, int max = N)
{
	T value = 0;
	for (int i = 0; i < max; i++)
	{
		value += vec[i];
	}
}

template <typename T, int N>
T reduceProduct(const Vector<T, N>& vec, int max = N)
{
	T value = 1;
	for (int i = 0; i < max; i++)
	{
		value *= vec[i];
	}
}

typedef Vector<int, 2> Vec2i;
typedef Vector<int, 3> Vec3i;
typedef Vector<float, 2> Vec2f;
typedef Vector<float, 3> Vec3f;
typedef Vector<double, 2> Vec2d;
typedef Vector<double, 3> Vec3d;
typedef Vector<Complexi, 2> Vec2ci;
typedef Vector<Complexf, 2> Vec2cf;
typedef Vector<Complexd, 2> Vec2cd;
typedef Vector<Complexi, 3> Vec3ci;
typedef Vector<Complexf, 3> Vec3cf;
typedef Vector<Complexd, 3> Vec3cd;

template <typename T> using Vec2 = Vector<T, 2>;
template <typename T> using Vec3 = Vector<T, 3>;

NameSpace_Math_End