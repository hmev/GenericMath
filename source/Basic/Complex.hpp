#pragma once

#include <cmath>
#include <Config.h>
#include <Basic/NumTrait.hpp>
#include <ostream>

NameSpace_Math_Begin

template <typename T>
struct Complex
{
public:
	T re, im;
public:
	Complex() : re(), im() {}
	template <typename T2>
	Complex(T2 real) : re(real) {}
	template <typename T2>
	Complex(T2 real, T2 imag) : re(real), im(imag) {}

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

	template<typename T2>
	bool operator==(const Complex<T2>& c) const 
	{
		typedef typename TraitPromoter<T, T2>::promoted promoted;
		return Trait<promoted>::equal(re, c.re) && Trait<promoted>::equal(c.im, c.im);
	}

	template <typename T2>
	bool operator==(const T2& _re) const
	{
		typedef typename TraitPromoter<T, T2>::promoted promoted;
		return Trait<promoted>::equal(re, _re) && Trait<promoted>::equal(im, 0);
	}

	template <typename T2>
	bool operator!=(const Complex<T2>& c) const
	{
		return re != c.re || im != c.im;
	}

public:
	Complex<T> operator-()
	{
		return std::move(Complex<T>(-re, -im));
	}

	template <typename T2>
	Complex<T>& operator+=(const T2& v)
	{
		re += v; 
		return (*this);
	}

	template <typename T2>
	Complex<T>& operator-=(const T2& v)
	{
		re -= v;
		return (*this);
	}

	template <typename T2>
	Complex<T>& operator*=(const T2& v)
	{
		re *= v;
		im *= v;
		return (*this);
	}

	template <typename T2>
	Complex<T>& operator/=(const T2& v)
	{
		re /= v;
		im /= v;
		return (*this);
	}

public:
	template <typename T2>
	Complex<T>& operator+=(const Complex<T2>& c)
	{
		re += c.re; im += c.im;
		return (*this);
	}
	template <typename T2>
	Complex<T>& operator-=(const Complex<T2>& c)
	{
		re -= c.re; im -= c.im;
		return (*this);
	}
	template <typename T2>
	Complex<T>& operator*=(const Complex<T2>& c)
	{
		T r = re * c.re - im * c.im;
		T i = re * c.im + im * c.re;
		re = r; im = i;
		return (*this);
	}
	template <typename T2>
	Complex<T>& operator/=(const Complex<T2>& c2)
	{
		Complex<T> c;
		T v = c2.re * c2.re + c2.im * c2.im;
		c.re = re * c2.re + im * c2.im;
		c.im = c2.re * im - re * c2.im;
		(*this) = c / v;
		return (*this);
	}
};

template <typename T>
Complex<T> I(const T& value)
{
	return std::move(Complex<T>(T(0), value)); 
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Complex<T>& c)
{
	os << c.re << "+" << c.im;
	return os;
}

template <typename T>
Complex<T> operator+(const Complex<T>& c1, const Complex<T>& c2)
{
	return std::move(Complex<T>(c1.re + c2.re, c1.im + c2.im));
}

template <typename T>
Complex<T> operator+(const T& c1, const Complex<T>& c2)
{
	return std::move(Complex<T>(c1 + c2.re, c2.im));
}

template <typename T>
Complex<T> operator+(const Complex<T>& c1, T& c2)
{
	return std::move(Complex<T>(c1.re + c2, c1.im));
}

template <typename T>
Complex<T> operator-(const Complex<T>& c1, const Complex<T>& c2)
{
	return std::move(Complex<T>(c1.re - c2.re, c1.im - c2.im));
}

template <typename T>
Complex<T> operator-(const T& c1, const Complex<T>& c2)
{
	return std::move(Complex<T>(c1 - c2.re, -c2.im));
}

template <typename T>
Complex<T> operator-(const Complex<T>& c1, const T& c2)
{
	return std::move(Complex<T>(c1.re - c2, c1.im));
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
Complex<T> operator*(const Complex<T>& c1, const T& v)
{
	return std::move(Complex<T>(c1.re * v, c1.im * v));
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

template <typename T>
Complex<T> operator/(const Complex<T>& c1, const T& v)
{
	return std::move(Complex<T>(c1.re / v, c1.im / v));
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



NameSpace_Math_End
