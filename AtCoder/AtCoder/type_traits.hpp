//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<type_traits>

namespace debug::type_traits
{
	template<class T>using true_t = std::true_type;
	template<class T>using false_t = std::false_type;

	namespace detail
	{
		template<class T>auto iterator_check_i(T const& v)
			->true_t<decltype((std::begin(v) != std::end(v)), *std::begin(v), ++std::begin(v))>;
		std::false_type iterator_check_i(...);
	}
	template<class T>constexpr bool iterator_check_v = decltype(detail::iterator_check_i(std::declval<T>()))::value;
}