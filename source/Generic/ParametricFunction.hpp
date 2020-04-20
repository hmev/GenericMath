#pragma once

/*

Interface of ParamtricFunction

template <typename ... Args>
struct ParametricFunction
{
	virtual T value(Args... arg) = 0;
};

*/

template <typename T, int N>
struct PolygonFunction
{
	Tensor<T, N> params;

	for (int i = 0; i < N; i++)
	{
		for (int i = 0; i < N; i++)
		{

		}
	}
};

template <typename T>
struct DiscreteFunction
{
	T value(Args... arg);

};
