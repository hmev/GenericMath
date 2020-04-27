#pragma once

#include <Vector>
#include <initializer_list>
#include <Config.h>
#include <Basic/Vector.hpp>

NameSpace_Math_Begin

struct Index
{
protected:
	std::vector<int> index;

public :
	Index() {}
	Index(int n) { index.push_back(n); }
	Index(int n, int m) { index.push_back(n); index.push_back(m); }
	Index(int n, int m, int k) { index.push_back(n); index.push_back(m); index.push_back(k); }
	Index(const std::initializer_list<int>& l) { for (auto i : l) index.push_back(i); }

	int volumn() const { int sz = 1; for (auto i : index) sz *= i; return sz; }
	int dim() const { return (int)index.size(); }
	void redim(unsigned  d) { return index.resize(d); }

	Index& operator=(Index ix)
	{
		index.clear();
		for (int i = 0; i < ix.dim(); i++)
		{
			index.push_back(ix[i]);
		}
		return (*this);
	}
	bool operator==(Index ix) const 
	{
		if (dim() != ix.dim()) return false;
		for (int i = 0; i < dim(); i++)
		{
			if (index[i] != ix[i]) return false;
		}
		return true;
	}
	bool operator!=(Index idx) const { return !((*this) == idx); }

	int& operator[](int i) { return index[i]; }
	int operator[](int i) const { return index[i]; }
	int& operator()(int i) { return index[i]; }
	int operator()(int i) const { return index[i]; }

public :
	int ind2sub(Index ix) const
	{
		const std::vector<int>& sz(index);
		int sub = ix[dim() - 1];
		for (int i = dim() - 2; i >= 0; i--)
		{
			sub = sub * sz[i] + sz[i - 1];
		}
		return sub;
	}

	Index sub2ind(int sub) const
	{
		const std::vector<int>& sz(index);
		Index ix;
		for (int i = 0; i < dim(); i++)
		{
			ix[i] = sub % sz[i];
			sub /= sz[i];
		}
		return ix;
	}
};

template <int D/*Dimension*/>
struct IndexD : public math::Vector <int, D >
{
public :
	typedef math::Vector<int, D> base_type;

	IndexD(){};

	int dim() const { return D; }

	// This Is Not Safe!
	void fromIndex(const Index& ix) { for (int i = 0; i < D; i++) this->data[i] = ix[i]; }
	// This Is Safe.
	Index toIndex() const { Index ix; for (int i = 0; i < D; i++) ix[i] = this->data[i]; return ix; }

public :
	int ind2sub(IndexD<D> ix) const
	{
		int sub = ix[ix.dim() - 1];
		for (int i = dim() - 2; i >= 0; i--)
		{
			sub = sub * this->data[i] + this->data[i - 1];
		}
		return sub;
	}

	IndexD<D> sub2ind(int sub) const
	{
		IndexD<D> ix;
		for (int i = 0; i < dim(); i++)
		{
			ix[i] = sub % this->data[i];
			sub /= this->data[i];
		}
		return ix;
	}
};

typedef IndexD<2> Index2;
typedef IndexD<3> Index3;

typedef Index Scale;

template <int D> using ScaleD = IndexD<D>;
typedef ScaleD<2> Scale2;
typedef ScaleD<3> Scale3;


NameSpace_Math_End