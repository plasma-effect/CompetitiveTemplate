//This source code is under the MIT License, see LICENSE.txt.
#include"graph.hpp"
#include"utility.hpp"
#include<boost/range/irange.hpp>
using namespace debug::utility;

namespace debug::graph
{
	bool connection_check(graph_t const& edge)
	{
		auto N = std::size(edge);
		union_find uf(N);
		for (auto i : boost::irange(N))
		{
			for (auto e : edge[i])
			{
				if (i < e)
				{
					break;
				}
				uf.merge(i, e);
			}
		}
		return uf.size() == 1;
	}
}