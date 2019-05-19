//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include"grobal_object.hpp"
#include<cstdint>
#include<vector>
#include<optional>
#include<boost/multi_array.hpp>
#include<boost/range/irange.hpp>

namespace debug::random
{
	namespace detail
	{
		template<class T>class next_function
		{
			std::uniform_int_distribution<T> dist;
			mutable std::optional<T> opt;
		public:
			next_function(T _min, T _max) :dist(_min, _max), opt()
			{

			}
			operator T()const
			{
				if (!opt)
				{
					opt = dist(debug::detail::obj.random);
				}
				return *opt;
			}
			T operator()()const
			{
				return dist(debug::detail::obj.random);
			}
		};
		class coin_function0
		{
			std::uniform_int_distribution<std::size_t> dist;
			std::size_t nume;
			mutable std::optional<bool> opt;
		public:
			coin_function0(std::size_t _d, std::size_t _n);
			operator bool()const;
			bool operator()()const;
		};
		class coin_function1
		{
			std::bernoulli_distribution ber;
			mutable std::optional<bool> opt;
		public:
			coin_function1(double _p);
			operator bool()const;
			bool operator()()const;
		};
	}
	detail::next_function<std::int64_t> next();
	template<class T>detail::next_function<T> next(T max);
	template<class T>detail::next_function<T> next(T min, T max);
	detail::coin_function0 coin(std::size_t denominator, std::size_t numerator);
	detail::coin_function1 coin(double p = 0.5);

	template<class T>std::vector<T> random_vector(std::size_t size, T min, T max);
	template<class T>std::vector<T> random_vector(std::size_t size, T max);
	template<class T>boost::multi_array<T, 2> random_dual_array(std::size_t H, std::size_t W, T min, T max);
	template<class T>boost::multi_array<T, 2> random_dual_array(std::size_t H, std::size_t W, T max);
}