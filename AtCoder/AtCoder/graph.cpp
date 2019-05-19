//This source code is under the MIT License, see LICENSE.txt.
#include"graph.hpp"
#include"random.hpp"
#include<boost/range/irange.hpp>
#include<boost/range/adaptor/transformed.hpp>
#include<boost/range/algorithm.hpp>
using namespace debug::utility;
using namespace debug::random;
namespace
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
			else if (coin(vec[index + s], vec[2 * (index + s)]))
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
		int random_get()
		{
			if (vec[1] == 0)
			{
				throw std::domain_error(R"(all flags are "false")");
			}
			return random_get_i(0, 1);
		}
	};
}

namespace debug::graph
{
	void write(graph_t const& edge, std::ostream& os)
	{
		std::size_t N = std::size(edge);
		std::size_t E = 0;
		for (auto const& set : edge)
		{
			E += set.size();
		}
		E /= 2;
		os << N << " " << E << std::endl;
		for (auto i : boost::irange(N))
		{
			for (auto e : edge[i])
			{
				if (i < e)
				{
					break;
				}
				os << e + 1 << " " << i + 1 << std::endl;
			}
		}
	}
	namespace
	{
		class graph_maker
		{
			random_exist_checker checker;
			std::size_t max_degree;
			std::size_t N;
			std::size_t E;
			graph_t graph;

			bool is_connect(int i, int j)
			{
				return graph[i].count(j);
			}

			bool connect(int i, int j)
			{
				if (!is_connect(i, j))
				{
					++E;
					graph[i].emplace(j);
					graph[j].emplace(i);
					if (graph[i].size() == max_degree)
					{
						checker[i] = false;
					}
					if (graph[j].size() == max_degree)
					{
						checker[j] = false;
					}
					return true;
				}
				return false;
			}

			bool cut(int i, int j)
			{
				if (is_connect(i, j))
				{
					--E;
					if (graph[i].size() == max_degree)
					{
						checker[i] = true;
					}
					if (graph[j].size() == max_degree)
					{
						checker[j] = true;
					}
					graph[i].erase(j);
					graph[j].erase(i);
					return true;
				}
				return false;
			}

			void connected_check()
			{
				if (max_degree == 0 && N > 1)
				{
					throw std::invalid_argument(R"(if max_degree is 0, N must be 1)");
				}
				else if (max_degree == 1 && N > 2)
				{
					throw std::invalid_argument(R"(if max_degree is 1, N must be 1 or 2)");
				}
			}
		public:
			graph_maker(std::size_t _N, std::size_t _max_degree) :
				checker(static_cast<int>(_N)),
				max_degree(std::min(_N - 1, _max_degree)),
				N(_N),
				E(),
				graph(_N)
			{
				if (N == 0)
				{
					throw std::invalid_argument(R"(it is impossible to make "0 size graph")");
				}
			}

			void make_connected_tree()
			{
				connected_check();
				auto index = indexed_vector<int>(N);
				boost::random_shuffle(index);
				checker[index[0]] = true;
				for (auto i : boost::irange<std::size_t>(1, N))
				{
					auto n = index[i];
					connect(checker.random_get(), n);
					checker[n] = true;
				}
			}

			void make_connected_graph(std::size_t edge)
			{
				if (edge > max_degree * N / 2)
				{
					throw std::invalid_argument(R"(connected graph whose max degree is equal to "max_degree" can't have edges more than [max_degree * N / 2])");
				}
				if (E == 0)
				{
					make_connected_tree();
				}
				while (E != edge)
				{
					int a, b;
					do
					{
						a = checker.random_get();
						b = checker.random_get();
					} while (a == b || is_connect(a, b));
					connect(a, b);
				}
			}

			graph_t&& get()
			{
				return std::move(graph);
			}
		};
	}
	graph_t make_random_tree(std::size_t N, std::size_t max_degree)
	{
		graph_maker maker(N, max_degree);
		maker.make_connected_tree();
		return maker.get();
	}
	graph_t make_random_graph(std::size_t N, std::size_t E, std::size_t max_degree)
	{
		graph_maker maker(N, max_degree);
		maker.make_connected_graph(E);
		return maker.get();
	}
	template<class T>weighted_graph_t<T> make_random_weighted_tree(std::size_t N, T min, T max, std::size_t max_degree)
	{
		return detail::make_weighted(make_random_tree(N, max_degree), next(min, max));
	}
#define MAKE_RANDOM_WEIGHTED_TREE(T) template weighted_graph_t<T> make_random_weighted_tree<T>(std::size_t N, T min, T max, std::size_t max_degree)
	INSTANCE_FOR_FOUR_BASIC_INTEGER(MAKE_RANDOM_WEIGHTED_TREE);

	template<class T>weighted_graph_t<T> make_random_weighted_graph(std::size_t N, std::size_t E, T min, T max, std::size_t max_degree)
	{
		return detail::make_weighted(make_random_graph(N, E, max_degree), next(min, max));
	}
#define MAKE_RANDOM_WEIGHTED_GRAPH(T) template weighted_graph_t<T> make_random_weighted_graph<T>(std::size_t N, std::size_t E, T min, T max, std::size_t max_degree)
	INSTANCE_FOR_FOUR_BASIC_INTEGER(MAKE_RANDOM_WEIGHTED_GRAPH);
}