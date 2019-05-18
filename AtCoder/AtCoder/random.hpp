//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include"grobal_object.hpp"
#include"utility.hpp"
#include<cstdint>
#include<vector>
#include<optional>
#include<boost/multi_array.hpp>
#include<boost/range/irange.hpp>

namespace debug::random
{
	namespace detail
	{
		struct next_t
		{
			template<class T>class function
			{
				T min;
				T max;
				mutable std::optional<T> opt;
			public:
				function(T _min, T _max) :min(_min), max(_max), opt()
				{

				}
				operator T()const
				{
					if (!opt)
					{
						std::uniform_int_distribution<T> dist(min, max);
						opt = dist(debug::detail::obj.random);
					}
					return *opt;
				}
				T operator()()const
				{
					std::uniform_int_distribution<T> dist(min, max);
					return dist(debug::detail::obj.random);
				}
			};
			function<std::int64_t> operator()()const;
			template<class T>auto operator()(T max)const
			{
				return function(T(), max);
			}
			template<class T>auto operator()(T min, T max)const
			{
				return function(min, max);
			}
		};
		struct coin_t
		{
			class function0
			{
				std::size_t deno;
				std::size_t nume;
				mutable std::optional<bool> opt;
			public:
				function0(std::size_t _d, std::size_t _n);
				operator bool()const;
				bool operator()()const;
			};
			class function1
			{
				std::bernoulli_distribution ber;
				mutable std::optional<bool> opt;
			public:
				function1(double _p);
				operator bool()const;
				bool operator()()const;
			};
			function0 operator()(std::size_t denominator, std::size_t numerator)const;
			function1 operator()(double p)const;
		};
	}
	constexpr detail::next_t next{};
	constexpr detail::coin_t coin{};
	template<class T>auto random_vector(std::size_t size, T min, T max)
	{
		auto f = next(min, max);
		std::vector<T> ret(size);
		for (auto& v : ret)
		{
			v = f();
		}
		return ret;
	}
	template<class T>auto random_vector(std::size_t size, T max)
	{
		return random_vector(size, T(), max);
	}
	template<class T>auto random_dual_array(std::size_t H, std::size_t W, T min, T max)
	{
		auto f = next(min, max);
		boost::multi_array<T, 2> ret(boost::extents[H][W]);
		for (auto i : boost::irange(H))
		{
			for (auto j : boost::irange(W))
			{
				ret[i][j] = f();
			}
		}
		return ret;
	}
	template<class T>auto random_dual_array(std::size_t H, std::size_t W, T max)
	{
		return random_dual_array(H, W, T(), max);
	}
}