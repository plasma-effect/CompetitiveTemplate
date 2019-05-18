//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<utility>
#include<limits>

namespace debug
{
	template<class T>constexpr T max_value = std::numeric_limits<T>::max();
	template<class T>constexpr T min_value = std::numeric_limits<T>::min();
}
