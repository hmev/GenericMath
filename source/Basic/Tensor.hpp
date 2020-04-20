#pragma once

#include <Vector>
#include <Math/Basic/Vector.hpp>
#include <Math/Basic/Index.hpp>

NameSpace_Math_Begin

/*

Tensor:

Similar to Array, but is dimension-fixed and volumn-fixed.
Only allow initiated from operator() and then assigned by value;

*/


template <typename T, int N>
class Tensor : private Array
{
	typedef Array<T, N> basetype;

public:
	Tensor() {}

	void predefine(IndexD<N> maxIndex)
	{
		maxI = maxIndex.toIndex();
		adjust();
	}
	IndexD<N> maxIndex() const
	{
		IndexD<N> index;
		index.fromIndex(basetype::maxIndex());
	}

public :

	T& operator()(const Index& ix) { return basetype(ix); }
	T operator()(const Index& ix) const { return basetype(ix); }

	bool sameAs(const Tensor<T, N>& arr) const 
	{ 
		return basetype::sameAs(*static_cast<basetype*>(&arr)); 
	}

};

NameSpace_Math_End