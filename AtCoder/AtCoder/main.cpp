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

std::pair<std::size_t, std::size_t> get_center(std::vector<std::set<std::size_t>> const& edge)
{
	std::queue<std::pair<std::size_t, std::size_t>> queue;
	queue.emplace(0, 0);
	boost::dynamic_bitset<> flag(edge.size());
	std::size_t start = 0;
	while (queue.size())
	{
		auto p = queue.front();
		queue.pop();
		auto i = p.first;
		if (flag[i])
		{
			continue;
		}
		start = i;
		flag[i] = true;
		for (auto&& n : edge[i])
		{
			queue.emplace(n, 0);
		}
	}
	queue.emplace(start, 0);
	std::vector<std::size_t> dist;
	while (queue.size())
	{
		auto p = queue.front();
		auto i = p.first;
		auto d = p.second;
		queue.pop();
		if (!flag[i])
		{
			continue;
		}
		flag[i] = false;
		if (dist.size() == d)
		{
			dist.emplace_back(i);
		}
		for (auto&& n : edge[i])
		{
			queue.emplace(n, d + 1);
		}
	}
	auto s = dist.size() - 1;
	return std::make_pair(s, dist[s / 2]);
}

void Main()
{
	std::size_t N;
	std::cin >> N;
	std::vector<std::set<std::size_t>> graph(N);
	for (int i : boost::irange(N - 1))
	{
		graph[i].emplace(i + 1);
		graph[i + 1].emplace(i);
	}
	debug::print::write_line(get_center(graph));
}

int main()
{
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(15);
	Main();
}