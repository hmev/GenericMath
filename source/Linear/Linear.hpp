#pragma once

#include <vector>

template<typename T, class V = std::vector<T>>
V&& linspace(T s0, T s1, size_t n)
{
	V ret;
	if (n == 0)
	{
		return ret;
	}

	if (n == 1)
	{
		ret.push_back(s0);
		return ret;
	}

	// n >= 2
	size_t m = n - 1;
	T a = 1.0 / m;
	for (size_t i = 0; i < n; ++i)
	{
		ret.push_back((s0 * (m - i) + s1 * i) * a);
	}
	return ret;
}

template<typename T, class V = std::vector<T>>
V&& step(T from, T step, T to)
{
	V ret;
	for (; from <= to; )
	{
		ret.push_back(from);
		from += step;
	}
	return ret;
}