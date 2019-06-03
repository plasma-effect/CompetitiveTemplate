//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<vector>
#include<set>
#include<map>
#include<boost/optional.hpp>
#include<boost/range/adaptor/transformed.hpp>
#include"utility.hpp"
#include"random.hpp"
#include"grobal_object.hpp"
#include"debug_print.hpp"

namespace debug::graph
{
	using graph_t = std::vector<std::set<std::size_t>>;
	template<class T>using weighted_graph_t = std::vector<std::map<std::size_t, T>>;

	template<class T>struct graph_traits
	{
		using value_type = typename T::value_type;
	};
	template<>struct graph_traits<graph_t>
	{
		using value_type = std::size_t;
	};
	template<class T>struct graph_traits<weighted_graph_t<T>>
	{
		using value_type = T;
	};
	template<class T>using graph_value_t = typename graph_traits<T>::value_type;

	bool is_connect(graph_t const& graph, std::size_t from, std::size_t to);
	template<class T>bool is_connect(weighted_graph_t<T> const& graph, std::size_t from, std::size_t to)
	{
		return graph[from].count(to);
	}

	boost::optional<std::size_t> distance(graph_t const& graph, std::size_t from, std::size_t to);
	template<class T> boost::optional<T> distance(weighted_graph_t<T>const& graph, std::size_t from, std::size_t to)
	{
		if (graph[from].count(to))
		{
			return graph[from].at(to);
		}
		else
		{
			return boost::none;
		}
	}

	void connect(graph_t& graph, std::size_t from, std::size_t to, std::size_t d);
	template<class T>void connect(weighted_graph_t<T>& graph, std::size_t from, std::size_t to, T const& d)
	{
		graph[from][to] = graph[to][from] = d;
	}

	void directed_connect(graph_t& graph, std::size_t from, std::size_t to, std::size_t d);
	template<class T>void directed_connect(graph_t& graph, std::size_t from, std::size_t to, T const& d)
	{
		graph[from][to] = d;
	}

	std::size_t degree(graph_t const& graph, std::size_t i);
	template<class T>std::size_t degree(weighted_graph_t<T>const& graph, std::size_t i)
	{
		return graph[i].size();
	}

	namespace detail
	{
		std::pair<std::size_t, std::size_t> trans(std::size_t i);
	}
	auto get_edges(graph_t const& graph, std::size_t i)
		->decltype(graph[i] | boost::adaptors::transformed(detail::trans));
	template<class T>decltype(auto) get_edges(weighted_graph_t<T> const& graph, std::size_t i)
	{
		return graph[i];
	}

	namespace detail
	{
		class random_exist_checker
		{
			std::vector<int> vec;
			std::size_t sz;
			std::size_t random_get_i(std::size_t index, std::size_t s)
			{
				if (s == sz)
				{
					return index;
				}
				else if (random::coin(vec[index + s], vec[2 * (index + s)]))
				{
					return random_get_i(2 * index, 2 * s);
				}
				else
				{
					return random_get_i(2 * index + 1, 2 * s);
				}
			}
			constexpr std::size_t get_size(int s)
			{
				if ((s & -s) == s)
				{
					return s;
				}
				while ((s & -s) != s)
				{
					s -= (s & -s);
				}
				return std::size_t(s) * 2;
			}
		public:
			random_exist_checker(int size) :vec(), sz(get_size(size))
			{
				vec.assign(2 * sz, 0);
			}
			class indexer
			{
				std::vector<int>& vec;
				std::size_t sz;
				std::size_t index;
			public:
				indexer(std::vector<int>& _vec, std::size_t _sz, std::size_t _index) :
					vec(_vec),
					sz(_sz),
					index(_index)
				{

				}
				indexer(indexer const&) = delete;
				indexer(indexer&&) = delete;
				indexer& operator=(indexer const&) = delete;
				indexer& operator=(indexer&&) = delete;

				operator bool()const
				{
					return vec[sz + index];
				}
				void operator=(bool f)
				{
					vec[sz + index] = f;
					for (auto s = (sz + index) / 2; s > 0; s /= 2)
					{
						vec[s] = vec[2 * s] + vec[2 * s + 1];
					}
				}
			};
			indexer operator[](std::size_t index)
			{
				return indexer(vec, sz, index);
			}
			std::size_t random_get()
			{
				if (vec[1] == 0)
				{
					throw std::domain_error(R"(all flags are "false")");
				}
				return random_get_i(0, 1);
			}
		};
		template<class Graph>struct graph_maker
		{
			using value_type = graph_value_t<Graph>;
			Graph graph;
			std::size_t vertexes, max_degree, edges;
			random_exist_checker checker;
			graph_maker(std::size_t _vertexes, std::size_t _max_degree) :
				graph(_vertexes),
				vertexes(_vertexes),
				max_degree(_max_degree),
				edges(),
				checker(_vertexes)
			{

			}

			void connect_check()
			{
				if (max_degree == 0 && vertexes > 1)
				{
					throw std::invalid_argument(R"(if [max_degree] is 0, [vertexes] must be 1)");
				}
				else if (max_degree == 1 && vertexes > 2)
				{
					throw std::invalid_argument(R"(if [max_degree] is 1, [vertexes] must be 1 or 2)");
				}
			}

			void inside_connect(std::size_t i, std::size_t j, value_type const& v)
			{
				connect(graph, i, j, v);
				++edges;
				if (degree(graph, i) == max_degree)
				{
					checker[i] = false;
				}
				if (degree(graph, j) == max_degree)
				{
					checker[j] = false;
				}
			}

			template<class Func>void make_tree(Func&& func)
			{
				connect_check();
				auto vec = utility::indexed_vector<std::size_t>(vertexes);
				boost::random_shuffle(vec);
				checker[vec[0]] = true;
				for (auto i : boost::irange<std::size_t>(1, vertexes))
				{
					inside_connect(vec[i], checker.random_get(), func());
					checker[vec[i]] = true;
				}
			}
			template<class Func>void make_graph(Func&& func, std::size_t E)
			{
				if (E > max_degree * vertexes / 2)
				{
					throw std::invalid_argument(R"(connected graph whose max degree is equal to [max_degree] can't have edges more than [max_degree * N / 2])");
				}
				if (edges == 0)
				{
					make_tree(func);
				}
				while (edges < E)
				{
					std::size_t i, j;
					do
					{
						i = checker.random_get();
						j = checker.random_get();
					} while (i == j || is_connect(graph, i, j));
					inside_connect(i, j, func());
				}
			}

			Graph&& get()
			{
				return std::move(graph);
			}
		};
	}
	template<class Graph>auto make_random_tree(std::size_t vertexes, std::size_t max_degree = utility::max_value<std::size_t>)
	{
		using value_type = graph_value_t<Graph>;
		max_degree = std::min(vertexes - 1, max_degree);
		detail::graph_maker<Graph> maker(vertexes, max_degree);
		maker.make_tree(utility::constant(value_type(1)));
		return maker.get();
	}
	template<class Graph>auto make_random_graph(std::size_t vertexes, std::size_t edges, std::size_t max_degree = utility::max_value<std::size_t>)
	{
		using value_type = graph_value_t<Graph>;
		max_degree = std::min(vertexes - 1, max_degree);
		detail::graph_maker<Graph> maker(vertexes, max_degree);
		maker.make_graph(utility::constant(value_type(1)), edges);
		return maker.get();
	}
	template<class Graph>auto make_weighted_random_tree(std::size_t vertexes, graph_value_t<Graph>const& min, graph_value_t<Graph> const& max, std::size_t max_degree = utility::max_value<std::size_t>)
	{
		max_degree = std::min(vertexes - 1, max_degree);
		detail::graph_maker<Graph> maker(vertexes, max_degree);
		maker.make_tree(random::next(min, max));
		return maker.get();
	}
	template<class Graph>auto make_weighted_random_graph(std::size_t vertexes, std::size_t edges, graph_value_t<Graph>const& min, graph_value_t<Graph> const& max, std::size_t max_degree = utility::max_value<std::size_t>)
	{
		max_degree = std::min(vertexes - 1, max_degree);
		detail::graph_maker<Graph> maker(vertexes, max_degree);
		maker.make_graph(random::next(min, max), edges);
		return maker.get();
	}
	template<class Graph>void write(Graph const& graph, bool is_weighted = false, bool is_directed = false, std::ostream& os = debug::detail::obj.ofs)
	{
		auto vertexes = size(graph);
		std::size_t edges = 0;
		for (auto i : boost::irange(vertexes))
		{
			edges += size(get_edges(graph, i));
		}
		if (!is_directed)
		{
			edges /= 2;
		}
		debug::print::detail::write(os, vertexes, edges);
		os << std::endl;
		for (auto i : boost::irange(vertexes))
		{
			for (auto&& [j, v] : get_edges(graph, i))
			{
				if (!is_directed && j < i)
				{
					continue;
				}
				if (is_weighted)
				{
					debug::print::detail::write(os, i + 1, j + 1, v);
				}
				else
				{
					debug::print::detail::write(os, i + 1, j + 1);
				}
				os << std::endl;
			}
		}
	}
}