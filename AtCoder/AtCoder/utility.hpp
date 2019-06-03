//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<utility>
#include<limits>
#include<set>
#include<map>
#include<vector>
#include"type_traits.hpp"

namespace debug::utility
{
	template<class T>constexpr T max_value = std::numeric_limits<T>::max();
	template<class T>constexpr T min_value = std::numeric_limits<T>::min();
	class union_find
	{
		std::vector<int> upper, rank;
		std::size_t dsize;
	public:
		union_find(std::size_t size) :upper(size, -1), rank(size, 0), dsize(size)
		{
		}

		int group(int index)
		{
			if (upper[index] == -1)
			{
				return index;
			}
			else
			{
				return upper[index] = group(upper[index]);
			}
		}

		bool merge(int x, int y)
		{
			auto gx = group(x);
			auto gy = group(y);
			if (gx != gy)
			{
				--dsize;
				if (rank[gx] < rank[gy])
				{
					upper[gx] = gy;
				}
				else if (rank[gx] > rank[gy])
				{
					upper[gy] = gx;
				}
				else
				{
					upper[gx] = gy;
					++rank[gx];
				}
				return true;
			}
			return false;
		}

		auto get()
		{
			std::map<int, std::set<int>> ret;
			for (int i = 0; i < upper.size(); ++i)
			{
				ret[group(i)].emplace(i);
			}
			return ret;
		}

		auto tops()
		{
			std::set<int> ret;
			for (int i = 0; i < upper.size(); ++i)
			{
				ret.emplace(group(i));
			}
			return ret;
		}

		bool is_same_group(int x, int y)
		{
			return group(x) == group(y);
		}

		std::size_t size()
		{
			return dsize;
		}
	};
	template<class T>std::vector<T> indexed_vector(std::size_t size)
	{
		std::vector<T> vec(size);
		T val{};
		for (auto& v : vec)
		{
			v = val;
			++val;
		}
		return vec;
	}
	template<class T>constexpr auto constant(T val)
	{
		return [val]
		{
			return val;
		};
	}
}
#define INSTANCE_FOR_FOUR_BASIC_INTEGER(macro)\
macro(std::int32_t);\
macro(std::uint32_t);\
macro(std::int64_t);\
macro(std::uint64_t)