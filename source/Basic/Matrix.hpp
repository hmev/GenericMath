#pragma once

#include <Vector>
#include <initializer_list>
#include "Math/Math.h"
#include "Math/Basic/Index.hpp"

NameSpace_Math_Begin

/*

Matrix

2-dimension tensor, fixed volume.

*/

template <typename T, int N, int M>
struct Matrix
{
protected:
	// The lower dim is continuous.
	// Please traverse matrix using :
	// for (int j = 0; j < M; j++)
	//     for (int i = 0; i < N; i++)
	//     {
    //     }
	T data[M][N];	

public:
	Matrix() 
	{
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)
			{
				data[i][j] = 0;
			}
	}
	Matrix(const T& v)
	{
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)
			{
				data[i][j] = v;
			}
	}

	Matrix(const std::initializer_list<T>& l)
	{
		int i = 0;
		for (auto iter = l.begin(); iter != l.end(); iter++)
		{
			if (i >= M*N)
				break;
			else
				data[i % M][i / M] = (*iter);
			i++;
		}
	}
	~Matrix() {}

	T operator()(int i, int j) const { return data[j][i]; }
	T& operator()(int i, int j) { return data[j][i]; }

	Matrix<T, N, M>& operator=(const Matrix<T, N, M>& m)
	{
		memcpy(data, m.data, N*M*sizeof(T));
		return (*this);
	}

	bool operator==(const Matrix<T, N, M>& m) const
	{
		for (int j = 0; j < M; j++)
			for (int i = 0; i < N; i++)
				if ((*this)(i, j) != m(i, j))
					return false;
		return true;
	}

	Matrix<T, N, M>& rmul(const Matrix<T, M, M>& m2)
	{
		Matrix<T, N, M> m1 = (*this);
		memset(data, 0, N*M * sizeof(T));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				for (int k = 0; k < M; k++)
					(*this)(i, k) += m1(i, j) * m2(j, k);
		return (*this);
	}

	Matrix<T, N, M>& lmul(const Matrix<T, N, N>& m1)
	{
		Matrix<T, N, M> m2 = (*this);
		memset(data, 0, N*M * sizeof(T));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < M; k++)
					(*this)(i, k) += m1(i, j) * m2(j, k);
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

template <typename T, int N>
Matrix<T, N, N> eye()
{
	Matrix<T, N, N> m;
	for (int i = 0; i < N; i++) m(i, i) = 0;
	return std::move(m);
}

/* unsafe */
template <typename T, int N, typename... Args>
Matrix<T, N, N> diag(Args... args)
{
	Matrix<T, N, N> m;
	for (int i = 0; i < N; i++) m(i, i) = args[i];
	return std::move(m);
}

template <int N, typename T>
Matrix<T, N, N> diag(const std::initializer_list<T>& list)
{
	Matrix<T, N, N> m;
	int i;
	for (auto iter = list.begin(); iter != list.end(); iter++) { m(i, i) = *iter; i++; }
	return std::move(m);
}

template <int N, typename T>
T rank(const Matrix<T, N, N>& m)
{
	// TODO
}

template <int N, typename T>
T trace(const Matrix<T, N, N>& m)
{
	T _trace;
	for (int i = 0; i < N; i++) _trace += m(i, i);
	return _trace;
}

typedef Matrix<int, 2, 2> Mat2i;
typedef Matrix<int, 3, 3> Mat3i;
typedef Matrix<double, 2, 2> Mat2d;
typedef Matrix<double, 3, 3> Mat3d;

NameSpace_Math_End