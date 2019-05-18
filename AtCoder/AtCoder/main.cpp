#include"bits/stdc++.h"
#include<boost/multi_array.hpp>
#include<boost/optional.hpp>
#include<boost/range/irange.hpp>
#include<boost/range/algorithm.hpp>
#include<boost/range/adaptor/reversed.hpp>
namespace adaptor = boost::adaptors;
template<class T>using p_queue = std::priority_queue<T, std::vector<T>, std::greater<>>;

void Main()
{
	using namespace debug::print;
	message(1, 2, 3);
	message(std::make_tuple(4, 5, 6));
	message(std::vector{ 7,8,9 });
	message();
	message(boost::multi_array<int, 2>(boost::extents[2][3]));
}

int main()
{
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(15);
	Main();
}