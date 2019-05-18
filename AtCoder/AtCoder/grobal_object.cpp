//This source code is under the MIT License, see LICENSE.txt.
#include"grobal_object.hpp"
#include<array>
#include<iomanip>

namespace debug::detail
{
	namespace
	{
		std::mt19937_64 make_randomizer()
		{
			std::array<std::uint64_t, 100> ar;
			std::random_device device;
			for (auto& v : ar)
			{
				v = device();
			}
			std::seed_seq seq(ar.begin(), ar.end());
			return std::mt19937_64(seq);
		}
	}
	global_object::global_object() :ofs("./debug.txt", std::ios_base::out | std::ios_base::trunc), random(make_randomizer())
	{
		std::cerr << std::fixed << std::setprecision(15);
		ofs << std::fixed << std::setprecision(15);
	}
	global_object obj{};
}
