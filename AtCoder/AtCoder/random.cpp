//This source code is under the MIT License, see LICENSE.txt.
#include"random.hpp"

namespace debug::random::detail
{
	next_t::function<std::int64_t> next_t::operator()() const
	{
		return function(min_value<std::int64_t>, max_value<std::int64_t>);
	}
	coin_t::function0::function0(std::size_t _d, std::size_t _n) :deno(_d), nume(_n), opt()
	{

	}
	coin_t::function0::operator bool()const
	{
		if (!opt)
		{
			opt = next(deno - 1) < nume;
		}
		return *opt;
	}
	bool coin_t::function0::operator()()const
	{
		return next(deno - 1) < nume;
	}
	coin_t::function1::function1(double _p) :ber(_p), opt()
	{

	}
	coin_t::function1::operator bool()const
	{
		if (!opt)
		{
			opt = ber(debug::detail::obj.random);
		}
		return *opt;
	}
	bool coin_t::function1::operator()()const
	{
		return ber(debug::detail::obj.random);
	}
	coin_t::function0 coin_t::operator()(std::size_t denominator, std::size_t numerator)const
	{
		return function0(denominator, numerator);
	}
	coin_t::function1 coin_t::operator()(double p)const
	{
		return function1(p);
	}
}