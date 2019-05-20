# graph.hpp
単純無向グラフのランダム生成関数、及び出力関数を提供する。  
このライブラリでは有向グラフは現状扱わない。  
全てnamespace debug::graph内に含まれている。
## グラフ型の定義について
debug::graph内では以下の型をグラフ型と定義している。
```cpp
using graph_t = std::vector<std::set<std::size_t>>;
template<class T>using weighted_graph_t = std::vector<std::map<std::size_t, T>>;
```
---
## void write(graph_t const& edge, std::ostream& os)
無向グラフedgeをosに出力する。osにはデフォルト引数として「./debug.txtを開いたstd::fstream型の変数」が渡されている。  
出力はNを頂点の数、Eを辺の数とし、頂点a_iとb_i(i=1, ..., E)の間に辺が存在する場合、以下のように出力される。ただし頂点の番号は1-indexedで扱われる。つまり、実際にedge内で扱われている数値に1を足したものが出力される。
>N E  
>a_1 b_1  
>...  
>a_E b_E
### 使用例
```cpp
void Main()
{
	using namespace debug::graph;
	graph_t graph(5);
	for (int i : boost::irange(0, 4))
	{
		graph[i].emplace(i + 1);
		graph[i + 1].emplace(i);
	}
	write(graph);//./debug.txtに出力される

	write(graph, std::cerr);//標準エラー出力に出力される
}
```
---
## template\<class T\>void write(weighted_graph_t\<T\>const& edge, std::ostream& os)
重み付き無向グラフedgeをosに出力する。osにはデフォルト引数として「./debug.txtを開いたstd::fstream型の変数」が渡されている。 
出力はNを頂点の数、Eを辺の数とし、頂点a_iとb_i(i=1, ..., E)の間に重みw_iの辺が存在する場合、以下のように出力される。ただし頂点の番号は1-indexedで扱われる。つまり、実際にedge内で扱われている数値に1を足したものが出力される。
>N E  
>a_1 b_1 w_1  
>...   
>a_E b_E w_E
### 使用例
```cpp
void Main()
{
	using namespace debug::graph;
	weighted_graph_t<int> graph(5);
	for (int i : boost::irange(0, 4))
	{
		graph[i][i + 1] = graph[i + 1][i] = i + 1;
	}
	write(graph);//./debug.txtに出力される

	write(graph, std::cerr);//標準エラー出力に出力される
}
```
---
## graph_t make_random_tree(std::size_t N, std::size_t max_degree)
最大の次数がmax_degreeである、頂点の数がNの木を返す。  
max_degreeのデフォルト引数としてstd::numeric_limits\<std::size_t\>::max()が渡されており、max_degreeがN以上の場合はN-1として扱われる。Nとmax_degreeは以下の条件を満たさなければならない(以下の関数も同様)。
- N \>= 1
- N == 2 のときmax_degree \>= 1
- N \>= 3 のときmax_degree \>= 2
### 使用例
```cpp
void Main()
{
	using namespace debug::graph;
	auto tree0 = make_random_tree(10);
	write(tree0);
	debug::print::write_line();

	auto tree1 = make_random_tree(10, 3);
	write(tree1);
}
```
---
## template\<class T\>weighted_graph_t\<T\> make_random_weighted_tree(std::size_t N, T min, T max, std::size_t max_degree)
最大の次数がmax_degreeであり、辺の重みがmin以上max以下である、頂点の数がNの重み付きの木を返す。  
Tは以下の型でなくてはならない。
- std::int32_t
- std::int64_t
- std::uint32_t
- std::uint64_t
### 使用例
```cpp
void Main()
{
	using namespace debug::graph;
	auto tree0 = make_random_weighted_tree(10, 1, 5);
	write(tree0);
	debug::print::write_line();

	auto tree1 = make_random_weighted_tree(10, 1LL, 5LL, 3);
	write(tree1);
}
```
---
## graph_t make_random_graph(std::size_t N, std::size_t E, std::size_t max_degree)
頂点の数がN、辺の数がEである、単純連結無向グラフを返す。  
NとEとmax_degreeの条件に以下の2つが追加される(次のmake_random_weighted_graphも同様)。
- E \< Nのとき、EはN-1として扱われる
- E \<= (N * max_degree) / 2
### 使用例
```cpp
void Main()
{
	using namespace debug::graph;
	auto graph0 = make_random_graph(10, 20);
	write(graph0);
	debug::print::write_line();

	auto graph1 = make_random_graph(10, 20, 5);
	write(graph1);
}
```
---
## template\<class T\>weighted_graph_t\<T\> make_random_weighted_graph(std::size_t N, std::size_t E, T min, T max, std::size_t max_degree)
最大の次数がmax_degreeであり、辺の重みがmin以上max以下である、頂点の数がNで辺の数がEのの重み付き単純連結無向グラフを返す。  
Tは以下の型でなくてはならない。
- std::int32_t
- std::int64_t
- std::uint32_t
- std::uint64_t
### 使用例
```cpp
void Main()
{
	using namespace debug::graph;
	auto graph0 = make_random_weighted_graph(10, 20, 1, 5);
	write(graph0);
	debug::print::write_line();

	auto graph1 = make_random_weighted_graph(10, 20, 1LL, 5LL, 5);
	write(graph1);
}
```