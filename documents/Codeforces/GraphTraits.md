# static class GraphTraits
無向グラフの文字列化及びランダム生成関数を提供する。
## グラフ型について
GraphTraits内ではグラフ型を  
重みなしのグラフをSortedSet\<int\>[]  
重みありのグラフをSortedDictionary\<int, T\>[]  
と定義している。
## public static string GraphString(this SortedSet\<int\>[] graph)
グラフを文字列として出力する。  
出力はNを頂点の数、Eを辺の数とし、頂点a_iとb_i(i=1, ..., E)の間に辺が存在する場合、以下のように出力される。ただし頂点の番号は1-indexedで扱われる。つまり、実際にgraph内で扱われている数値に1を足したものが出力される。
>N E  
>a_1 b_1  
>...  
>a_E b_E
### 使用例
```csharp
static void Main(string[] args)
{
    var graph = new SortedSet<int>[5];
    foreach(var i in Range(0, 5))
    {
        graph[i] = new SortedSet<int>();
    }
    foreach(var i in Range(0, 4))
    {
        graph[i].Add(i + 1);
        graph[i + 1].Add(i);
    }
    WriteLine(Debug.GraphTraits.GraphString(graph));
}
```
---
## public static string GraphString\<T\>(SortedDictionary\<int, T\>[] graph)
重み付きグラフを文字列として出力する。  
出力はNを頂点の数、Eを辺の数とし、頂点a_iとb_i(i=1, ..., E)の間に重みw_iの辺が存在する場合、以下のように出力される。ただし頂点の番号は1-indexedで扱われる。つまり、実際にedge内で扱われている数値に1を足したものが出力される。
>N E  
>a_1 b_1 w_1  
>...   
>a_E b_E w_E
### 使用例
```csharp
static void Main(string[] args)
{
    var graph = new SortedDictionary<int, int>[5];
    foreach(var i in Range(0, 5))
    {
        graph[i] = new SortedDictionary<int, int>();
    }
    foreach(var i in Range(0, 4))
    {
        var j = i + 1;
        graph[i][j] = graph[j][i] = i + 1;
    }
    WriteLine(Debug.GraphTraits.GraphString(graph));
}
```
---
## public static SortedSet\<int\>[] RandomTree(int N, int maxDegree = int.MaxValue)
最大の次数がmaxDegreeである、頂点数がNの木を返す。  
maxDegreeのデフォルト引数としてint.MaxValueが渡されており、maxDegreeがN以上のときN-1として扱われる。NとmaxDegreeは以下の条件を満たさなければならない(以下の関数も同様)。
- N \>= 1
- N == 2 のときmaxDegree \>= 1
- N \>= 3 のときmaxDegree \>= 2
### 使用例
```csharp
static void Main(string[] args)
{
    var tree0 = Debug.GraphTraits.RandomTree(10);
    WriteLine(Debug.GraphTraits.GraphString(tree0));
            
    var tree1 = Debug.GraphTraits.RandomTree(10, 3);
    WriteLine(Debug.GraphTraits.GraphString(tree1));
}
```
---
## public static SortedDictionary\<int, int\>[] RandomWeightedTree(int N, int minValue, int maxValue, int maxDegree = int.MaxValue)
最大の次数がmaxDegreeであり、辺の重みがminValue以上maxValue以下である、頂点数がNの重み付きの木を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var tree0 = Debug.GraphTraits.RandomWeightedTree(10, 1, 5);
    WriteLine(Debug.GraphTraits.GraphString(tree0));

    var tree1 = Debug.GraphTraits.RandomWeightedTree(10, 1, 5, 3);
    WriteLine(Debug.GraphTraits.GraphString(tree1));
}
```
---
## public static SortedDictionary\<int, long\>[] RandomWeightedTree(int N, long minValue, long maxValue, int maxDegree = int.MaxValue)
最大の次数がmaxDegreeであり、辺の重みがminValue以上maxValue以下である、頂点数がNの重み付きの木を返す。  
引数の型でオーバーロードしていることに注意せよ。  
またSystem.Randomを内部で利用している都合上
- minValueはint.MinValue以上
- maxValueはint.MaxValue未満

でなくてはならない(以下のRandomWeightedGraphも同様)。
### 使用例
```csharp
static void Main(string[] args)
{
    var tree0 = Debug.GraphTraits.RandomWeightedTree(10, 1L, 5L);
    WriteLine(Debug.GraphTraits.GraphString(tree0));

    var tree1 = Debug.GraphTraits.RandomWeightedTree(10, 1L, 5L, 3);
    WriteLine(Debug.GraphTraits.GraphString(tree1));
}
```
---
## public static SortedSet\<int\>[] RandomGraph(int N, int E, int maxDegree = int.MaxValue)
最大の次数がmaxDegreeであり、頂点の数がN、辺の数がEである、単純連結無向グラフを返す。  
NとEとmaxDegreeの条件に以下の2つが追加される(次のRandomWeightedGraphも同様)。
- E \< Nのとき、EはN-1として扱われる
- E \<= (N * maxDegree) / 2
### 使用例
```csharp
static void Main(string[] args)
{
    var graph0 = Debug.GraphTraits.RandomGraph(10, 20);
    WriteLine(Debug.GraphTraits.GraphString(graph0));

    var graph1 = Debug.GraphTraits.RandomGraph(10, 20, 5);
    WriteLine(Debug.GraphTraits.GraphString(graph1));
}
```
---
## public static SortedDictionary\<int, int\>[] RandomWeightedGraph(int N, int E, int minValue, int maxValue, int maxDegree = int.MaxValue)
最大の次数がmaxDegreeであり、辺の重みがminValue以上maxValue以下、頂点の数がNで辺の数がEの重み付きグラフを返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var graph0 = Debug.GraphTraits.RandomWeightedGraph(10, 20, 1, 5);
    WriteLine(Debug.GraphTraits.GraphString(graph0));

    var graph1 = Debug.GraphTraits.RandomWeightedGraph(10, 20, 1, 5, 5);
    WriteLine(Debug.GraphTraits.GraphString(graph1));
}
```
---
## public static SortedDictionary\<int, long\>[] RandomWeightedGraph(int N, int E, long minValue, long maxValue, int maxDegree = int.MaxValue)
最大の次数がmaxDegreeであり、辺の重みがminValue以上maxValue以下、頂点の数がNで辺の数がEの重み付きグラフを返す。  
引数の型でオーバーロードしていることに注意せよ。
### 使用例
```csharp
static void Main(string[] args)
{
    var graph0 = Debug.GraphTraits.RandomWeightedGraph(10, 20, 1L, 5L);
    WriteLine(Debug.GraphTraits.GraphString(graph0));

    var graph1 = Debug.GraphTraits.RandomWeightedGraph(10, 20, 1L, 5L, 5);
    WriteLine(Debug.GraphTraits.GraphString(graph1));
}
```