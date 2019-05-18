//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<type_traits>

namespace debug
{
	template<class T>using true_t = std::true_type;
	template<class T>using false_t = std::false_type;
}