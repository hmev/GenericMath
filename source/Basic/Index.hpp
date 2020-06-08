#pragma once

#include <Vector>
#include <initializer_list>
#include <Config.h>
#include <Basic/Vector.hpp>

NameSpace_Math_Begin

/// 
/// \brief Expandable index.
/// 
struct Index
{
protected:
	std::vector<int> index;

public :
	Index() {}
	Index(int n) { index.resize(1); index[0] = n; }
	Index(int n, int m) { index.resize(2); index[0] = n; index[1] = m; }
	Index(int n, int m, int k) { index.resize(3); index[0] = n; index[1] = m; index[2] = k;}
	Index(const std::initializer_list<int>& l) 
	{ 
		for (auto i : l) index.push_back(i); 
		index.resize(index.size());
	}

	int volume() const { int sz = 1; for (auto i : index) sz *= i; return sz; }
	int dim() const { return (int)index.size(); }
	void redim(unsigned  d) { return index.resize(d); }

	Index& operator=(Index ix)
	{
		index.clear();
		index.resize(ix.dim());
		for (int i = 0; i < ix.dim(); i++)
		{
			index[i] = ix[i];
		}		
		return (*this);
	}

	bool operator!=(Index idx) const { return !((*this) == idx); }

	int& operator[](int i) { return index[i]; }
	int operator[](int i) const { return index[i]; }
	int& operator()(int i) { return index[i]; }
	int operator()(int i) const { return index[i]; }

public:

	bool operator==(Index ix) const 
	{
		if (dim() != ix.dim()) return false;
		for (int i = 0; i < dim(); i++)
		{
			if (index[i] != ix[i]) return false;
		}
		return true;
	}

	bool operator<(Index idx) const 
	{
		if (dim() > idx.dim()) return false;
		if (dim() < idx.dim()) return true;

		for (int i = dim() - 1; i > 0; i--)
		{
			if (index[i] > idx[i]) return false;
			if (index[i] < idx[i]) return true;
		}
		return true;
	}

	bool operator>(Index idx) const 
	{
		if (dim() > idx.dim()) return true;
		if (dim() < idx.dim()) return false;

		for (int i = dim() - 1; i > 0; i--)
		{
			if (index[i] > idx[i]) return true;
			if (index[i] < idx[i]) return false;
		}
		return true;
	}

	bool innerThan(Index idx) const 
	{
		if (dim() > idx.dim()) return false;

		for (int i = 0; i < dim(); i++)
		{
			if (index[i] > idx[i]) return false;
		}
		return true;
	}	

	bool outerThan(Index idx) const 
	{
		if (dim() < idx.dim()) return false;

		for (int i = 0; i < idx.dim(); i++)
		{
			if (index[i] < idx[i]) return false;
		}
		return true;
	}		

public:

	/// 
	/// \brief Turn to Sub
	/// Example: 
	///		Space: 2, 3
	///
	///     Index: 0, 1
	///     Sub  : 2
	///
	///     Index: 1, 1
	///     Sub  : 3
	///
	///     Index: 1, 2
	///     Sub  : 5
	/// 
	/// Example:
	///     Space: 2, 3, 5
	///     
	///     Index: 0, 1, 1
	///     Sub  : 8
	/// 
	///		Index: 1, 3, 4
	///     Sub  : 31
	///      
	/// \param ix 
	/// \return int 
	/// 
	int ind2sub(Index ix) const
	{
		// static_assert(outerThan(ix));
		const std::vector<int>& scale(index);

		int sub = ix[dim() - 1];
		for (int i = dim() - 2; i >= 0; i--)
		{
			sub = sub * scale[i] + ix[i];
		}
		return sub;
	}

	Index sub2ind(int sub) const
	{
		// static_assert(volume() > sub);
		const std::vector<int>& scale(index);
		Index ix;
		ix.redim(dim());
		for (int i = 0; i < dim(); i++)
		{
			ix[i] = sub % scale[i];
			sub /= scale[i];
		}
		return ix;
	}
};

template <int D/*Dimension*/>
struct IndexD
{
protected:
	int index[D];
public:
	typedef math::Vector<int, D> base_type;

	IndexD(){};

	int dim() const { return D; }

	// This Is Not Safe!
	void fromIndex(const Index& ix) { for (int i = 0; i < D; i++) this->index[i] = ix[i]; }
	// This Is Safe.
	Index toIndex() const { Index ix; for (int i = 0; i < D; i++) ix[i] = this->index[i]; return ix; }

public:
	IndexD<D>& operator=(IndexD<D> ix)
	{
		for (int i = 0; i < ix.dim(); i++)
		{
			index[i] = ix[i];
		}		
		return (*this);
	}
	bool operator==(IndexD<D> ix) const 
	{
		if (dim() != ix.dim()) return false;
		for (int i = 0; i < dim(); i++)
		{
			if (index[i] != ix[i]) return false;
		}
		return true;
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
	bool operator!=(IndexD<D> idx) const { return !((*this) == idx); }

	int& operator[](int i) { return index[i]; }
	int operator[](int i) const { return index[i]; }
	int& operator()(int i) { return index[i]; }
	int operator()(int i) const { return index[i]; }

	int ind2sub(IndexD<D> ix) const
	{
		int sub = ix[ix.dim() - 1];
		for (int i = dim() - 2; i >= 0; i--)
		{
			sub = sub * this->index[i] + this->index[i - 1];
		}
		return sub;
	}

	IndexD<D> sub2ind(int sub) const
	{
		IndexD<D> ix;
		for (int i = 0; i < dim(); i++)
		{
			ix[i] = sub % index[i];
			sub /= index[i];
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