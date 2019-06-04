//This source code is under the MIT License, see LICENSE.txt.
#include"graph.hpp"
#include"random.hpp"
#include<boost/range/irange.hpp>
#include<boost/range/adaptor/transformed.hpp>
#include<boost/range/algorithm.hpp>
using namespace debug::utility;

namespace debug::graph
{
	bool is_connect(inside_type::graph_t const& graph, std::size_t from, std::size_t to)
	{
		return graph[from].count(to);
	}
	void connect(inside_type::graph_t& graph, std::size_t from, std::size_t to, std::size_t d)
	{
		graph[from].insert(to);
		graph[to].insert(from);
	}
	std::size_t degree(inside_type::graph_t const& graph, std::size_t i)
	{
		return graph[i].size();
	}
	auto get_edges(inside_type::graph_t const& graph, std::size_t i)
		-> decltype(graph[i] | boost::adaptors::transformed(detail::trans))const&
	{
		return graph[i] | boost::adaptors::transformed(detail::trans);
	}
	namespace detail
	{
		std::pair<std::size_t, std::size_t> trans(std::size_t i)
		{
			return std::pair<std::size_t, std::size_t>(i, 1);
		}
	}
}
