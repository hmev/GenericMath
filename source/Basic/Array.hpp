#pragma once

#include <Vector>
#include <Tuple>
#include <initializer_list>
#include <Config.h>
#include <Basic/Index.hpp>
#include <Basic/FuncTrait.hpp>

NameSpace_Math_Begin

template <typename T>
struct Array
{
protected :
	Scale sc;
	std::vector<T> data;

	typedef Array<T> thistype;

public :
	Array() {}
	Array(const Scale& sc)
	{
		resize(sc);
	}
	Array(const Scale& sc, const std::initializer_list<T>& list)
	{		
		for (auto v : list) data.push_back(v);
		resize(sc);
	}
	~Array() {}

public :
	int volume() const { return sc.volume(); };
	Scale scale() const { return sc; };

	void adjust() { data.resize(volume()); }
	void resize(const Scale& _sc) { sc = _sc; adjust(); }
	void resize(const int n) { resize(Index(n)); }
	void resize(const int n, const int m) { resize(Scale(n, m)); }
	void resize(const int n, const int m, const int k) { resize(Scale(n, m, k)); }

	void raise(int theNewLength) 
	{ 
		sc.redim(sc.dim() + 1);
		sc[sc.dim()] = theNewLength;  
		adjust();
	}
	void reduce()
	{
		sc.redim(sc.dim() - 1);
		adjust();
	}

public:
	T& operator()(const Index& ix) { return data[sc.ind2sub(ix)]; }
	T operator()(const Index& ix) const { return data[sc.ind2sub(ix)]; }

	void copy(const Array<T>& arr)
	{
		sc = arr.sc;
		data = arr.data;
	}

	void operator=(const Array<T>& arr)
	{
		copy(arr);
	}

	bool operator==(const Array<T>& arr) const
	{
		if (sc != arr.sc) return false;
		for (int i = 0; i < volume(); i++)
			if (data[i] != arr.data[i])
				return false;
		return true;
	}

	template <int N>
	bool operator==(const Vector<T, N>& arr) const
	{
		/* Unsafe */
		if (volume() != N) return false;
		return arr == data;
	}

public: 

	template <template<typename T> class Container>
	Container<T> convert()
	{
		Container<T> container;
		for (auto value in data)
		{
			container.push_back(value);
		}
		return container;
	}
};


NameSpace_Math_End
