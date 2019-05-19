//This source code is under the MIT License, see LICENSE.txt.
#include"utility.hpp"
#include"debug_print.hpp"
#include"random.hpp"
#include"graph.hpp"
#include<boost/format.hpp>

namespace
{
	class test_object
	{
		std::vector<int> vec;
		boost::multi_array<int, 2> ar;
		std::tuple<int, std::string, std::nullptr_t> t;
		std::tuple<
			std::pair<std::string, std::array<std::int32_t, 2>>,
			std::pair<std::string, std::array<std::uint32_t, 2>>,
			std::pair<std::string, std::array<std::int64_t, 2>>,
			std::pair<std::string, std::array<std::uint64_t, 2>>> vals;
	public:
		test_object() :vec(3), ar(boost::extents[3][3]), t(1, "string", nullptr), vals(
			std::pair<std::string, std::array<std::int32_t, 2>>(" std::int32_t", { 1,10 }),
			std::pair<std::string, std::array<std::uint32_t, 2>>("std::uint32_t", { 1u,10u }),
			std::pair<std::string, std::array<std::int64_t, 2>>(" std::int64_t", { 1LL,10LL }),
			std::pair<std::string, std::array<std::uint64_t, 2>>("std::uint64_t", { 1ULL,10ULL }))
		{
			for (auto i : boost::irange(3))
			{
				vec[i] = i + 1;
				for (auto j : boost::irange(3))
				{
					ar[i][j] = 3 * i + j;
				}
			}
		}
		template<class... Ts>auto format(const char* base, Ts... args)
		{
			return (boost::format(base) % ... % args);
		}
		template<class Func>void write_all(Func func)
		{
			func(std::get<0>(vals));
			func(std::get<1>(vals));
			func(std::get<2>(vals));
			func(std::get<3>(vals));
		}

		void test_debug_print()
		{
			using namespace debug::print;
			write_line("--- debug_print.hpp ---");
			write(1, 2, 3);
			write(" endline");

			write_line();
			write_line(1, 2, 3);
			write_line(t);
			write_line(vec);
			write_line();
			write_line(ar);
			write_line();

			write_range(vec);

			message(1, 2, 3);
			message(t);
			message(vec);
			message();
			message(ar);
			message();

			message_range(vec);
			
			write_line();
		}
		void test_random()
		{
			using debug::print::write_line;
			auto write_next1 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line(format("next(%1%)(for variable):", str), debug::random::next(ar[1]));
			};
			auto write_next2 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line(format("next(%1%, %1%)(for variable):", str), debug::random::next(ar[0], ar[1]));
			};
			auto write5 = [](auto const& str, auto const& f)
			{
				write_line(str, f(), f(), f(), f(), f());
			};
			auto write_next_func1 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write5(format("next(%1%)(for function):", str), debug::random::next(ar[1]));
			};
			auto write_next_func2 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write5(format("next(%1%)(for function):", str), debug::random::next(ar[0], ar[1]));
			};
			auto write_vector1 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line(format("random_vector(std::size_t, %1%):", str), debug::random::random_vector(5, ar[1]));
			};
			auto write_vector2 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line(format("random_vector(std::size_t, %1%, %1%):", str), debug::random::random_vector(5, ar[0], ar[1]));
			};
			auto write_dual_array1 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line();
				write_line(format("random_dual_array(std::size_t, std::size_t, %1%):", str));
				write_line(debug::random::random_dual_array(3, 3, ar[1]));
			};
			auto write_dual_array2 = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line();
				write_line(format("random_dual_array(std::size_t, std::size_t, %1%, %1%):", str));
				write_line(debug::random::random_dual_array(3, 3, ar[0], ar[1]));
			};

			write_line("--- random.hpp ---");
			write_line("next():", debug::random::next());
			write_line();

			write_all(write_next1);
			write_line();
			
			write_all(write_next2);
			write_line();
			
			write_all(write_next_func1);
			write_line();

			write_all(write_next_func2);
			write_line();

			write5("next()(for function):", debug::random::next());
			write_line();

			write_line("coin(std::size_t, std::size_t)(for variable):", debug::random::coin(2, 5));
			write_line("coin(double)(for variable):", debug::random::coin(0.7));
			write_line("coin()(for variable):", debug::random::coin());
			write_line();

			write5("coin(std::size_t, std::size_t)(for function):", debug::random::coin(2, 5));
			write5("coin(double)(for function):", debug::random::coin(0.7));
			write5("coin()(for function):", debug::random::coin());
			write_line();

			write_all(write_vector1);
			write_line();

			write_all(write_vector2);
			
			write_all(write_dual_array1);
			write_all(write_dual_array2);
		}
		bool connect_check(debug::graph::graph_t const& edge)
		{
			auto N = std::size(edge);
			debug::utility::union_find uf(N);
			for (auto i : boost::irange(N))
			{
				for (auto e : edge[i])
				{
					if (i < e)
					{
						continue;
					}
					uf.merge(i, e);
				}
			}
			return uf.size() == 1;
		}
		void test_graph()
		{
			using debug::print::write_line;
			using debug::print::message;
			using namespace debug::graph;
			write_line("--- graph.hpp ---");
			constexpr std::size_t count = 10000;
			constexpr std::size_t N = 100;
			constexpr std::size_t E = 200;
			message("connection check(random tree)");
			bool f = true;
			for (auto c : boost::irange(count))
			{
				if (c % (count / 100) == 0)
				{
					message("check:", c / (count / 100), "%");
				}
				if (!connect_check(make_random_tree(N)))
				{
					message("detect disconnection forest");
					write_line("detect disconnection forest");
					f = false;
					break;
				}
			}
			if (f)
			{
				message(format("all %1% forest is connected", count));
				write_line(format("all %1% forest is connected", count));
			}
			
			message("connection check(random graph)");
			f = true;
			for (auto c : boost::irange(count))
			{
				if (c % (count / 100) == 0)
				{
					message("check:", c / (count / 100), "%");
				}
				if (!connect_check(make_random_graph(N, E)))
				{
					message("detect disconnection graph");
					write_line("detect disconnection graph");
					f = false;
					break;
				}
			}
			if (f)
			{
				message(format("all %1% graph is connected", count));
				write_line(format("all %1% graph is connected", count));
			}

			write_line("write(graph_t const&, std::ostream&)");
			write_line("make_random_tree(std::size_t, std::size_t)");
			write(make_random_tree(10));
			write_line();

			write_line("make_random_tree(std::size_t, std::size_t, std::size_t)");
			write(make_random_graph(10, 20));
			write_line();

			auto tree = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line(format("make_random_weighted_tree(std::size_t, %1%, %1%, std::size_t)", str));
				write(make_random_weighted_tree(10, ar[0], ar[1]));
				write_line();
			};
			auto graph = [&](auto const& p)
			{
				auto const& [str, ar] = p;
				write_line(format("make_random_weighted_graph(std::size_t, std::size_t, %1%, %1%, std::size_t)", str));
				write(make_random_weighted_graph(10, 20, ar[0], ar[1]));
			};
			write_line("write(weighted_graph_t<T>const&, std::ostream&)");
			write_all(tree);
			write_all(graph);
		}
	};
}

void debug::utility::test()
{
	test_object tester{};

	tester.test_debug_print();
	tester.test_random();
	tester.test_graph();
}
