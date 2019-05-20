//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<vector>
#include<set>
#include<map>
#include"utility.hpp"
#include"grobal_object.hpp"
#include"debug_print.hpp"

namespace debug::graph
{
	using graph_t = std::vector<std::set<std::size_t>>;
	template<class T>using weighted_graph_t = std::vector<std::map<std::size_t, T>>;

	void write(graph_t const& edge, std::ostream& os = debug::detail::obj.ofs);
	template<class T>void write(weighted_graph_t<T>const& edge, std::ostream& os = debug::detail::obj.ofs)
	{
		std::size_t N = std::size(edge);
		std::size_t E = 0;
		for (auto const& map : edge)
		{
			E += map.size();
		}
		E /= 2;
		os << N << " " << E << std::endl;
		for (auto i : boost::irange(N))
		{
			for (auto ite = edge[i].lower_bound(i); ite != std::cend(edge[i]); ++ite)
			{
				auto const& [e, v] = *ite;
				debug::print::detail::write(os, i + 1, e + 1, v);
				os << std::endl;
			}
		}
	}

	namespace detail
	{
		template<class Func>auto make_weighted(graph_t const& base, Func func)
		{
			auto N = std::size(base);
			weighted_graph_t<decltype(func())> ret(N);
			for (auto i : boost::irange(N))
			{
				for (auto e : base[i])
				{
					if (i < e)
					{
						break;
					}
					ret[i][e] = ret[e][i] = func();
				}
			}
			return ret;
		}
	}
	graph_t make_random_tree(std::size_t N, std::size_t max_degree = debug::utility::max_value<std::size_t>);
	graph_t make_random_graph(std::size_t N, std::size_t E, std::size_t max_degree = debug::utility::max_value<std::size_t>);
	template<class T>weighted_graph_t<T> make_random_weighted_tree(std::size_t N, T min, T max, std::size_t max_degree = debug::utility::max_value<std::size_t>);
	template<class T>weighted_graph_t<T> make_random_weighted_graph(std::size_t N, std::size_t E, T min, T max, std::size_t max_degree = debug::utility::max_value<std::size_t>);
}