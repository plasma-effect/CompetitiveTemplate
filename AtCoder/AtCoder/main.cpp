#include"bits/stdc++.h"
#include<boost/multi_array.hpp>
#include<boost/optional.hpp>
#include<boost/range/irange.hpp>
#include<boost/range/algorithm.hpp>
#include<boost/range/adaptor/reversed.hpp>
#include<boost/operators.hpp>
#include<boost/dynamic_bitset.hpp>
namespace adaptor = boost::adaptors;
template<class T>using p_queue = std::priority_queue<T, std::vector<T>, std::greater<>>;
typedef std::vector<std::set<std::size_t>> graph_t;
typedef std::vector<std::map<std::size_t, int>> weighted_graph_t;

void Main()
{
	using namespace debug::graph;
	auto a = make_random_tree<::graph_t>(10);
	auto b = make_random_graph<::graph_t>(10, 15);
	auto c = make_weighted_random_tree<::weighted_graph_t>(10, 1, 5);
	auto d = make_weighted_random_graph<::weighted_graph_t>(10, 15, 1, 5);
	write(a, true, false, std::cout);
	std::cout << std::endl;
	write(b, true, false, std::cout);
	std::cout << std::endl;
	write(c, true, false, std::cout);
	std::cout << std::endl;
	write(d, true, false, std::cout);
	
}

int main()
{
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(15);
	Main();
}