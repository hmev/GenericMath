#pragma once

#include <cmath>
#include <Config.h>
#include <Basic/NumTrait.hpp>
#include <Basic/Vector.hpp>

NameSpace_Math_Begin

template <typename T>
struct Complex
{
public:
	T re, im;
public:
	Complex() : re(), im() {}

	Complex(T real, T imag) : re(real), im(imag) {}

	T real() { return re; }
	T imag() { return im; }

	double mod()  { return sqrt(re * re + im * im); }
	double angle()  { return atan2(im, re); }
	double angleDeg() { return RAD2DEG(angle()); }

	Complex<T>& operator=(const T& v)
	{
		re = v;
		return (*this);
	}

	Complex<T>& operator=(const Complex<T>& c)
	{
		re = c.re; im = c.im;
		return (*this);
	}

	bool operator==(const Complex<T>& c) const 
	{
		return re == c.re && im == c.im;
	}

	bool operator!=(const Complex<T>& c) const
	{
		return re != c.re || im != c.im;
	}

public:
	Complex<T>& operator+=(const T& v)
	{
		re += v; 
		return (*this);
	}
	Complex<T>& operator-=(const T& v)
	{
		re -= v;
		return (*this);
	}
	Complex<T>& operator*=(const T& v)
	{
		re *= v;
		im *= v;
		return (*this);
	}
	Complex<T>& operator/=(const T& v)
	{
		re /= v;
		im /= v;
		return (*this);
	}

public:
	Complex<T>& operator+=(const Complex<T>& c)
	{
		re += c.re; im += c.im;
		return (*this);
	}
	Complex<T>& operator-=(const Complex<T>& c)
	{
		re -= c.re; im -= c.im;
		return (*this);
	}
	Complex<T>& operator*=(const Complex<T>& c)
	{
		T r = re * c.re - im * c.im;
		T i = re * c.im + im * c.re;
		re = r; im = i;
		return (*this);
	}
	Complex<T>& operator/=(const Complex<T>& c2)
	{
		Complex<T> c;
		T v = c2.re * c2.re + c2.im * c2.im;
		c.re = re * c2.re + im * c2.im;
		c.im = c2.re * im - re * c2.im;
		(*this) = c;
		return (*this);
	}
};

template <typename T>
Complex<T> operator+(const Complex<T>& c1, const Complex<T>& c2)
{
	Complex<T> c;
	c.re = c1.re + c2.re;
	c.im = c1.im + c2.im;
	return c;
}

template <typename T>
Complex<T> operator-(const Complex<T>& c1, const Complex<T>& c2)
{
	Complex<T> c;
	c.re = c1.re - c2.re;
	c.im = c1.im - c2.im;
	return c;
}

template <typename T>
Complex<T> operator*(const Complex<T>& c1, const Complex<T>& c2)
{
	Complex<T> c;
	c.re = c1.re * c2.re - c1.im * c2.im;
	c.im = c1.re * c2.im + c1.im * c2.re;
	return c;
}

template <typename T>
Complex<T> operator/(const Complex<T>& c1, const Complex<T>& c2)
{
	Complex<T> c;
	T v = c2.re * c2.re + c2.im * c2.im;
	c.re = c1.re * c2.re + c1.im * c2.im;
	c.im = c2.re * c1.im - c1.re * c2.im;

	c /= v;
	return c;
}

template <typename T1, typename T2>
Complex<typename TraitPromoter<T1, T2>::promoted> operator+(const Complex<T1>& c1, const Complex<T2>& c2)
{
	Complex<typename TraitPromoter<T1, T2>::promoted> c;
	c.re = c1.re + c2.re;
	c.im = c1.im + c2.im;
	return c;
}

template <typename T1, typename T2>
Complex<typename TraitPromoter<T1, T2>::promoted> operator-(const Complex<T1>& c1, const Complex<T2>& c2)
{
	Complex<typename TraitPromoter<T1, T2>::promoted> c;
	c.re = c1.re - c2.re;
	c.im = c1.im - c2.im;
	return c;
}

template <typename T1, typename T2>
Complex<typename TraitPromoter<T1, T2>::promoted> operator*(const Complex<T1>& c1, const Complex<T2>& c2)
{
	Complex<typename TraitPromoter<T1, T2>::promoted> c;
	c.re = c1.re * c2.re - c1.im * c2.im;
	c.im = c1.re * c2.im + c1.im * c2.re;
	return c;
}

template <typename T1, typename T2>
Complex<typename TraitPromoter<T1, T2>::promoted> operator/(const Complex<T1>& c1, const Complex<T2>& c2)
{
	typedef FloatPromoter<typename TraitPromoter<T1, T2>::promoted>::type T;
	Complex<T> c;
	T v = c2.re * c2.re + c2.im * c2.im;
	c.re = c1.re * c2.re + c1.im * c2.im;
	c.im = c2.re * c1.im - c1.re * c2.im;

	c /= v;
	return c;
}

typedef Complex<int> Complexi;
typedef Complex<float> Complexf;
typedef Complex<double> Complexd;

typedef Vector<Complexi, 2> Vec2ci;
typedef Vector<Complexf, 2> Vec2cf;
typedef Vector<Complexd, 2> Vec2cd;

NameSpace_Math_End
