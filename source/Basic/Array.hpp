#pragma once

#include <Vector>
#include <initializer_list>
#include "Math/Math.h"
#include "Math/Basic/Index.hpp"

NameSpace_Math_Begin

/*

Array: 

An extensible and dimension-flexible array, but no reductant volume after adjust.
The lower dimension is memory tight than the higher, which means you need to traverse it like:

	for (int z = 0; z < zmax; z++)
	{
		for (int y = 0; y < ymax; y++)
		{
			for (int x = 0; x < xmax; x++)
			{
		
			}
		}
	}

*/



template <typename T>
struct Array
{
protected :
	Index maxI;
	std::vector<T> data;

public :
	Array() {}
	Array(const Index& ix)
	{
		resize(ix);
	}
	Array(const Index& ix, const std::initializer_list<T>& list)
	{
		resize(ix);
		for (auto v : list) data.push_back(v);
	}
	~Array() {}

public :
	int volumn() const { return maxI.volumn(); };
	Index maxIndex() const { return maxI; };

	void adjust() { data.resize(maxI.volumn()); }
	void resize(const Index& ix) { maxI = ix; adjust(); }
	void resize(const int n) { resize(Index(n)); }
	void resize(const int n, const int m) { resize(Index(n, m)); }
	void resize(const int n, const int m, const int k) { resize(Index(n, m, k)); }

	void raise(int theNewLength) 
	{ 
		maxI.redim(maxI.dim() + 1);
		maxI[maxI.dim()] = theNewLength;  
		adjust();
	}
	void reduce()
	{
		maxI.redim(maxI.dim() - 1);
		adjust();
	}
public :
	T& operator()(const Index& ix) { return data[maxI.ind2sub(ix)]; }
	T operator()(const Index& ix) const { return data[maxI.ind2sub(ix)]; }

	void copy(const Array<T>& arr)
	{
		maxI = arr.maxI;
		data = arr.data;
	}

	bool sameAs(const Array<T>& arr) const
	{
		if (maxI != arr.maxI) return false;
		for (int i = 0; i < volumn(); i++)
			if (data[i] != arr.data[i])
				return false;
		return true;
	}
};

//// Access parts of the array dims in a certain order. 
//template <typename T, args ...>
//class ArrayAccessor
//{
//public :
//
//};

NameSpace_Math_End
