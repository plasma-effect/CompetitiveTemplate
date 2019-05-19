//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<vector>
#include<set>
#include<map>

namespace debug::graph
{
	using graph_t = std::vector<std::set<std::size_t>>;
	template<class T>using weighted_graph_t = std::vector<std::map<std::size_t, T>>;
	namespace detail
	{
		
	}
	bool connection_check(graph_t const& edge);
}