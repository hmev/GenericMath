#ifndef __MATH_BASIC_Index_H__
#define __MATH_BASIC_Index_H__

#include <Vector>
#include <initializer_list>
#include "Math/Math.h"
#include "Math/Basic/Vector.hpp"

NameSpace_Math_Begin

struct Index
{
protected:
	std::vector<unsigned int> index;

public :
	Index() {}
	Index(unsigned int n) { index.push_back(n); }
	Index(unsigned int n, unsigned int m) { index.push_back(n); index.push_back(m); }
	Index(unsigned int n, unsigned int m, unsigned int k) { index.push_back(n); index.push_back(m); index.push_back(k); }
	Index(const std::initializer_list<unsigned int>& l) { for (auto i : l) index.push_back(i); }

	unsigned int volumn() const { unsigned int sz = 1; for (auto i : index) sz *= i; return sz; }
	unsigned int dim() const { return (unsigned int)index.size(); }
	void redim(unsigned  d) { return index.resize(d); }

	Index& operator=(Index ix)
	{
		index.clear();
		for (unsigned int i = 0; i < ix.dim(); i++)
		{
			index.push_back(ix[i]);
		}
		return (*this);
	}
	bool operator==(Index ix) const 
	{
		if (dim() != ix.dim()) return false;
		for (unsigned int i = 0; i < dim(); i++)
		{
			if (index[i] != ix[i]) return false;
		}
		return true;
	}
	bool operator!=(Index idx) const { return !((*this) == idx); }

	unsigned int& operator[](int i) { return index[i]; }
	unsigned int operator[](int i) const { return index[i]; }
	unsigned int& operator()(int i) { return index[i]; }
	unsigned int operator()(int i) const { return index[i]; }

public :
	int ind2sub(Index ix) const
	{
		const std::vector<unsigned int>& sz(index);
		int sub = ix[dim() - 1];
		for (unsigned int i = dim() - 2; i >= 0; i--)
		{
			sub = sub * sz[i] + sz[i - 1];
		}
		return sub;
	}

	Index sub2ind(unsigned int sub) const
	{
		const std::vector<unsigned int>& sz(index);
		Index ix;
		for (unsigned int i = 0; i < dim(); i++)
		{
			ix[i] = sub % sz[i];
			sub /= sz[i];
		}
		return ix;
	}
};

template <unsigned int D/*Dimension*/>
struct IndexD : public math::Vector <unsigned int, D >
{
public :
	typedef math::Vector<unsigned int, D> base_type;

	IndexD(){};

	unsigned int dim() const { return D; }

	// This Is Not Safe!
	void fromIndex(const Index& ix) { for (unsigned int i = 0; i < D; i++) this->data[i] = ix[i]; }
	// This Is Safe.
	Index toIndex() const { Index ix; for (unsigned int i = 0; i < D; i++) ix[i] = this->data[i]; return ix; }

public :
	unsigned int ind2sub(IndexD<D> ix) const
	{
		int sub = ix[ix.dim() - 1];
		for (unsigned int i = dim() - 2; i >= 0; i--)
		{
			sub = sub * this->data[i] + this->data[i - 1];
		}
		return sub;
	}

	IndexD<D> sub2ind(unsigned int sub) const
	{
		IndexD<D> ix;
		for (unsigned int i = 0; i < dim(); i++)
		{
			ix[i] = sub % this->data[i];
			sub /= this->data[i];
		}
		return ix;
	}
};

typedef IndexD<2> Index2;
typedef IndexD<3> Index3;

NameSpace_Math_End

#endif