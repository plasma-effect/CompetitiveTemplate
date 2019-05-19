//This source code is under the MIT License, see LICENSE.txt.
#include"random.hpp"
using namespace debug::utility;
using namespace debug::detail;

namespace debug::random
{
	namespace detail
	{
		coin_function0::coin_function0(std::size_t _d, std::size_t _n) :dist(_d - 1), nume(_n), opt()
		{

		}
		coin_function0::operator bool() const
		{
			if (!opt)
			{
				opt = dist(obj.random) < nume;
			}
			return *opt;
		}
		bool coin_function0::operator()() const
		{
			return dist(obj.random) < nume;
		}
		coin_function1::coin_function1(double _p) :ber(_p), opt()
		{

		}
		coin_function1::operator bool() const
		{
			if (!opt)
			{
				opt = ber(obj.random);
			}
			return *opt;
		}
		bool coin_function1::operator()() const
		{
			return ber(obj.random);
		}
	}

	detail::next_function<std::int64_t> next()
	{
		return detail::next_function(min_value<std::int64_t>, max_value<std::int64_t>);
	}

	template<class T>detail::next_function<T> next(T max)
	{
		return detail::next_function(T(), max);
	}
#define NEXT1(T)template detail::next_function<T> next<T>(T max);
	NEXT1(std::int32_t);
	NEXT1(std::int64_t);
	NEXT1(std::uint32_t);
	NEXT1(std::uint64_t);
	
	template<class T>detail::next_function<T> next(T min, T max)
	{
		return detail::next_function(min, max);
	}
#define NEXT2(T)template detail::next_function<T> next<T>(T min, T max)
	NEXT2(std::int32_t);
	NEXT2(std::int64_t);
	NEXT2(std::uint32_t);
	NEXT2(std::uint64_t);


	detail::coin_function0 coin(std::size_t denominator, std::size_t numerator)
	{
		return detail::coin_function0(denominator, numerator);
	}
	detail::coin_function1 coin(double p)
	{
		return detail::coin_function1(p);
	}

	template<class T>std::vector<T> random_vector(std::size_t size, T min, T max)
	{
		auto f = next(min, max);
		std::vector<T> ret(size);
		for (auto& v : ret)
		{
			v = f();
		}
		return ret;
	}
#define RANDOM_VECTOR2(T) template std::vector<T> random_vector<T>(std::size_t size, T min, T max)
	RANDOM_VECTOR2(std::int32_t);
	RANDOM_VECTOR2(std::int64_t);
	RANDOM_VECTOR2(std::uint32_t);
	RANDOM_VECTOR2(std::uint64_t);

	template<class T>std::vector<T> random_vector(std::size_t size, T max)
	{
		return random_vector(size, T(), max);
	}
#define RANDOM_VECTOR1(T) template std::vector<T> random_vector<T>(std::size_t size, T max)
	RANDOM_VECTOR1(std::int32_t);
	RANDOM_VECTOR1(std::int64_t);
	RANDOM_VECTOR1(std::uint32_t);
	RANDOM_VECTOR1(std::uint64_t);

	template<class T>boost::multi_array<T, 2> random_dual_array(std::size_t H, std::size_t W, T min, T max)
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
#define RANDOM_DUAL_ARRAY2(T) template boost::multi_array<T, 2> random_dual_array<T>(std::size_t H, std::size_t W, T min, T max)
	RANDOM_DUAL_ARRAY2(std::int32_t);
	RANDOM_DUAL_ARRAY2(std::int64_t);
	RANDOM_DUAL_ARRAY2(std::uint32_t);
	RANDOM_DUAL_ARRAY2(std::uint64_t);

	template<class T>boost::multi_array<T, 2> random_dual_array(std::size_t H, std::size_t W, T max)
	{
		return random_dual_array(H, W, T(), max);
	}
#define RANDOM_DUAL_ARRAY1(T) template boost::multi_array<T, 2> random_dual_array<T>(std::size_t H, std::size_t W, T max)
	RANDOM_DUAL_ARRAY1(std::int32_t);
	RANDOM_DUAL_ARRAY1(std::int64_t);
	RANDOM_DUAL_ARRAY1(std::uint32_t);
	RANDOM_DUAL_ARRAY1(std::uint64_t);
}