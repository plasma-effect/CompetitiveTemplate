//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<iostream>
#include<fstream>
#include<random>

namespace debug::detail
{
	struct global_object
	{
		std::fstream ofs;
		std::mt19937_64 random;
		global_object();
	};
	extern global_object obj;
}