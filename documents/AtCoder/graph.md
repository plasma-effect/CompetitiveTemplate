# graph.hpp
単純無向グラフのランダム生成関数、及び出力関数を提供する。  
全てnamespace debug::graph内に含まれている。
## グラフ型の定義について
このライブラリではグラフ型は以下のいずれかを満たす型と定義している。
- std::vector\<std::set\<std::size_t\>\>
- 型Tに対しstd::vector\<std::map\<std::size_t, T\>\>
- 次の条件を全て満たす型Graph
	- コンストラクタGraph(std::size_t)を持つ
	- 0-indexedである
	- メンバ型value_typeを持っている
	- ADLで呼び出せる以下のフリー関数が全て存在する
		- size(graph_t const& graph)
		- is_connect(Graph const&, std::size_t, std::size_t)
		- connect(Graph&, std::size_t, std::size_t, value_type)
		- degree(Graph const& graph, std::size_t)
		- get_edges(Graph const& graph, std::size_t)

上のフリー関数は以下の性質を持たなければならない。
- size(Graph const& graph)
	- graphの頂点数を返す
- is_connect(Graph const& graph, std::size_t i, std::size_t j)
	- 頂点iとjが接続されているならtrue、そうでないならfalseを返す
- connect(Graph& graph, std::size_t i, std::size_t j, value_type d)
	- 頂点iとjの間に重みdの辺を張る
- degree(Graph const& graph, std::size_t i)
	- 頂点iでの次数を返す
- get_edges(Graph const& graph, std::size_t i)
	- 頂点iから出る辺を全て持つRangeを返す
	- ただしRangeの各要素は2変数に分解できる型でなければならない。例えばstd::pair\<std::size_t, value_type\>など
	- また2変数[j, v]に分解されたとき、jは他方の頂点を、vは辺の重みを表さなければならない
## template\<class Graph\>void write(Graph const& graph, bool is_weighted, bool is_directed, std::ostream& os)
graphをosに出力する。各引数の意味は以下の通り。
- graph
	- 出力されるグラフ
- is_weighted
	- 重み付きグラフとして扱うかどうかのフラグ、デフォルトではfalse
		- これがtrueであって、Graphがstd::vector\<std::set\<std::size_t\>\>のとき、各辺の重みは全て1として扱われる
- is_directed
	- 有向グラフとして扱うかどうかのフラグ、デフォルトではfalse
- os
	-出力先の出力ストリーム。デフォルトでは「./debug.txtを開いたstd::fstream型の変数」

graphの頂点数をN、辺の数をEとし、頂点a_iとb_i(i=1, ..., E)の間に重みがd_iである辺が存在する場合、以下のように出力される。ただし頂点の番号は1-indexedで扱われる。つまり、実際にedge内で扱われている数値に1を足したものが出力される。  
また内部でdebug::print::write_lineの内部実装を利用しているので、is_weightedがfalseであってもd_iはdebug::print内の関数で使えるものでなくてはならない。
### is_weightedがfalseのとき
>N E  
>a_1 b_1  
>...  
>a_E b_E  
### is_weightedがtrueのとき
>N E  
>a_1 b_1 d_1  
>...  
>a_E b_E d_E
### 使用例
```cpp
void Main()
{
	typedef std::vector<std::map<std::size_t, int>> graph_t;
	using namespace debug::graph;
	
	graph_t graph(5);
	for (auto i : boost::irange(0, 4))
	{
		graph[i][i + 1] = graph[i + 1][i] = i + 1;
	}
	write(graph);

	write(graph, true, false, std::cout);
}
```
---
## template\<class Graph\>auto make_random_tree(std::size_t vertexes, std::size_t max_degree = std::numeric_limits\<std::size_t\>::max())
頂点の数がvertexes、最大次数がmax_degreeである木を返す。  
グラフはGraph型として構築される。またtemplate引数は省略できない。(以下の関数も同様)  
vertexesとmax_degreeは以下の条件を満たさなければならない(以下の関数も同様)。
- vertexes >= 1
- vertexes == 2 のときmax_degree >= 1
- vertexes >= 3 のときmax_degree >= 2
### 使用例
```cpp
void Main()
{
	typedef std::vector<std::set<std::size_t>> graph_t;
	using namespace debug::graph;
	
	auto tree0 = make_random_tree<graph_t>(10);
	write(tree0);
	debug::print::write_line();
	auto tree1 = make_random_tree<graph_t>(10, 3);
	write(tree1);
}
```
---
## template\<class Graph\>auto make_random_weighted_tree(std::size_t vertexes, value_type const& min, value_type const& max, std::size_t max_degree)
頂点の数がvertexes、最大次数がmax_degreeであり、辺の重みがmin以上max以下の重み付きの木を返す。  
value_typeは辺の重みを表す型である。  
また内部でdebug::random::nextを使っているためvalue_typeは以下の型でなくてはならない。
- std::int32_t
- std::uint32_t
- std::int64_t
- std::uint64_t
### 使用例
```cpp
void Main()
{
	typedef std::vector<std::map<std::size_t, int>> graph_t;
	using namespace debug::graph;
	
	auto tree0 = make_random_weighted_tree<graph_t>(10, 1, 5);
	write(tree0, true);
	debug::print::write_line();

	auto tree1 = make_random_weighted_tree<graph_t>(10, 1, 5, 3);
	write(tree1, true);
}
```
## template\<class Graph\>auto make_random_graph(std::size_t vertexes, std::size_t edges, std::size_t max_degree)
頂点の数がvertexes、辺の数がedges、最大次数がmax_degreeである無向グラフを返す。  
vertexesとedgesとmax_degreeに以下の条件が追加される(次のmake_random_weighted_graphも同様)
- edges \< vertexesのときedgesはvertexes - 1として扱われる
- edges \<= (vertexes * max_degree) / 2
### 使用例
```cpp
void Main()
{
	typedef std::vector<std::set<std::size_t>> graph_t;
	using namespace debug::graph;
	
	auto graph0 = make_random_graph<graph_t>(10, 15);
	write(graph0);
	debug::print::write_line();

	auto graph1 = make_random_graph<graph_t>(10, 15, 5);
	write(graph1);
}
```
## template\<class Graph\>auto make_random_weighted_graph(std::size_t vertexes, std::size_t edges, value_type const& min, value_type const& max, std::size_t max_degree)
頂点の数がvertexes、辺の数がedges、最大次数がmax_degreeであり、辺の重みがmin以上max以下である重み付き無向グラフを返す。  
value_typeは辺の重みを表す型である。  
また内部でdebug::random::nextを使っているためvalue_typeは以下の型でなくてはならない。
- std::int32_t
- std::uint32_t
- std::int64_t
- std::uint64_t
### 使用例
```cpp
void Main()
{
	typedef std::vector<std::map<std::size_t, int>> graph_t;
	using namespace debug::graph;

	auto graph0 = make_random_weighted_graph<graph_t>(10, 15, 1, 5);
	write(graph0, true);
	debug::print::write_line();

	auto graph1 = make_random_weighted_graph<graph_t>(10, 15, 1, 5, 5);
	write(graph1, true);
}
```