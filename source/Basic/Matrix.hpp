#pragma once

#include <Vector>
#include <initializer_list>
#include <Config.h>
#include <Basic/Index.hpp>

NameSpace_Math_Begin

/// 
/// \brief Tiny Matrix 
/// 
/// Matrix vs Array
/// Matrix is scale-fixed 2D Array. 
/// It has more mathematical support than Array, such as left 
/// multiple and right multiple.
///
/// Matrix vs Tensor
/// Matrix is 2D Tensor. 
///
/// Sample of Matrix:
/// Matrix<double, 2, 3> m = {
///		{0, 1}
///     {2, 3}
///     {4, 5}
/// };
///
/// \tparam T int, long, float, double, etc. 
/// \tparam N length of the first dimension.
/// \tparam M length of the second diemension.
/// 
template <typename T, int N, int M>
struct Matrix
{
private:

	/// \brief Storage of Matrix
	/// 
	/// !!IMPORTANT!!
	/// The lower dim is memory compact.
	/// The better traverse loop is:
	/// for (int j = 0; j < M; j++)
	///     for (int i = 0; i < N; i++)
	///     {
    ///     }
	///
	/// !!IMPORTANT!!
	/// NEVER indexing this raw data directly.
	/// Instead, use the operator(), such as (*this)(i, j)
	/// 
	T data[M][N];

protected:
	typedef Matrix<T, N, M> thistype;

public:
	Matrix() 
	{
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)
			{
				data[j][i] = 0;
			}
	}
	Matrix(const T& v)
	{
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)
			{
				data[j][i] = v;
			}
	}

	/// 
	/// \brief Construct a new Matrix object
	/// Example: 	
	///	Matrix<double, 2, 3> m({
	/// 	{0, 1, 2}, 
	/// 	{3, 4, 5},		
	/// });
	/// \param list a two-dimension initializer_list indicating the matrix.  
	/// WARNING: initializer_list is the transpose of the storage member "data".
	/// 
	Matrix(const std::initializer_list<Vector<T, M>>& list)
	{
		int i = 0;
		for (auto iter = list.begin(); iter != list.end(); iter++)
		{
			for (int j = 0; j < M; i++)
			{
				(*this)(i, j) = (*iter)[j];
			}
			i++;
		}
	}

	~Matrix() {}

	T operator()(int i, int j) const { return data[j][i]; }
	T& operator()(int i, int j) { return data[j][i]; }

	void operator=(const Matrix<T, N, M>& m)
	{
		memcpy(data, m.data, N*M*sizeof(T));		
	}

	/// 
	/// \brief Assign Matrix object
	/// Example: 	
	///	Matrix<double, 2, 3> m = {
	/// 	{0, 1, 2}, 
	/// 	{3, 4, 5},		
	/// };
	///
	/// \param list a two-dimension initializer_list indicating the matrix
	/// WARNING: initializer_list is the transpose of the storage member "data".
	/// \return thistype&
	/// 
	void operator=(const std::initializer_list<Vector<T, M>>& list)
	{
		int i = 0;
		for (auto iter = list.begin(); iter != list.end(); iter++)
		{
			for (int j = 0; j < M; i++)
			{
				(*this)(i, j) = (*iter)[j];
			}
			i++;
		}		
	}

	bool operator==(const Matrix<T, N, M>& m) const
	{
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)
				if ((*this)(i, j) != m(i, j))
					return false;
		return true;
	}

	bool operator!=(const Matrix<T, N, M>& m) const
	{
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)
				if ((*this)(i, j) != m(i, j))
					return true;
		return false;
	}

	/// 
	/// \brief covariance vector
	/// 
	/// \param j colume of matrix
	/// \return Vector<T, N> covariance vector
	/// 
	Vector<T, N> vector(int j) const
	{
		Vector<T, N> v;
		for (int i = 0; i < N; i++)
		{
			v[i] = (*this)(i, j);
		}
		return std::move(v);
	}

	/// 
	/// \brief contravariance vector
	/// 
	/// \param j row of matrix
	/// \return Vector<T, N> contravariance vector
	/// 
	Vector<T, M> tvector(int i) const
	{
		Vector<T, M> v;
		for (int j = 0; j < N; i++)
		{
			v[j] = (*this)(i, j);
		}
		return std::move(v);
	}

	thistype& rmul(const Matrix<T, M, M>& m2)
	{
		Matrix<T, N, M> m1 = (*this);
		memset(data, 0, N*M * sizeof(T));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				for (int k = 0; k < M; k++)
					(*this)(i, k) += m1(i, j) * m2(j, k);

		return (*this);
	}

	thistype& lmul(const Matrix<T, N, N>& m1)
	{
		Matrix<T, N, M> m2 = (*this);
		memset(data, 0, N*M * sizeof(T));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < M; k++)
					(*this)(i, k) += m1(i, j) * m2(j, k);

		return (*this);
	}

	thistype& transpose()
	{
		//static_assert(N == M);
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < j; i++)
			{
				std::swap((*this)(i, j), (*this)(j, i));
			}
		}
		return (*this);
	}

	template <typename F>
	thistype& inPlaceCalc(F&& func)
	{
		for (int j = 0; j < M; j++)
		{
			for (int i = 0; i < N; i++)
			{
				(*this)(i, j) = f((*this)(i,j));
			}
		}
		return (*this);
	}
};

template <typename T, int N, int M, int L>
Matrix<T, N, L> mul(const Matrix<T, N, M>& m1, const Matrix<T, M, L>& m2)
{
	Matrix<T, N, L> m;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			for (int k = 0; k < L; k++)
				m(i, k) += m1(i, j) * m2(j, k);
	return std::move(m);
}

template <typename T, int N, int M, int L>
Matrix<T, N, L> operator*(const Matrix<T, N, M>& m1, const Matrix<T, M, L>& m2)
{
	return std::move(mul(m1, m2));
}

template <typename T, int N>
Matrix<T, N, N> transpose(const Matrix<T, N, N>& matrix)
{
	Matrix<T, N, N> m = matrix;
	m.transpose();
	return std::move(m);
}

template <typename T, int N, int M>
Matrix<T, N, M> inPlaceAdd(const Matrix<T, N, M>& m1, const Matrix<T, N, M>& m2)
{
	Matrix<T, N, M> m;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			m(i, j) = m1(i, j) + m2(i, j);
	return std::move(m);
}

template <typename T, int N, int M>
Matrix<T, N, M> inPlaceMul(const Matrix<T, N, M>& m1, const Matrix<T, N, M>& m2)
{
	Matrix<T, N, M> m;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)			
				m(i, j) = m1(i, j) * m2(i, j);
	return std::move(m);
}

template <typename T, int N, int M>
T reduceMul(const Matrix<T, N, M>& m1, const Matrix<T, N, M>& m2)
{
	T sum = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			sum += m1(i, j) * m2(i, j);
	return sum;
}

class MatrixCreator
{
public:

	template <typename T, int N, int M>
	static Matrix<T, N, M> zero()
	{
		Matrix<T, N, M> m;
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < M; j++)
				m(i, j) = 0;
		return std::move(m);
	}

	template <typename T, int N>
	static Matrix<T, N, N> eye()
	{
		Matrix<T, N, N> m;
		for (int i = 0; i < N; i++) m(i, i) = 1;
		return std::move(m);
	}

	/* unsafe */
	template <typename T, int N, typename... Args>
	static Matrix<T, N, N> diag(Args... args)
	{
		Matrix<T, N, N> m;
		for (int i = 0; i < N; i++) m(i, i) = args[i];
		return std::move(m);
	}

	template <typename T, int N>
	static Matrix<T, N, N> diag(const std::initializer_list<T>& list)
	{
		Matrix<T, N, N> m;
		int i;
		for (auto iter = list.begin(); iter != list.end(); iter++) { m(i, i) = *iter; i++; }
		return std::move(m);
	}
};

typedef Matrix<int, 2, 2> Mat2i;
typedef Matrix<int, 3, 3> Mat3i;
typedef Matrix<double, 2, 2> Mat2d;
typedef Matrix<double, 3, 3> Mat3d;

NameSpace_Math_End