//This source code is under the MIT License, see LICENSE.txt.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Linq.Enumerable;

namespace Codeforces.Debug
{
    static class GraphTraits
    {
        static SortedSet<int>[] MakeDefaultGraph(int size)
        {
            var ret = new SortedSet<int>[size];
            foreach (var i in Range(0, size))
            {
                ret[i] = new SortedSet<int>();
            }
            return ret;
        }
        static SortedDictionary<int, T>[] MakeDefaultWeightedGraph<T>(int size)
        {
            var ret = new SortedDictionary<int, T>[size];
            foreach (var i in Range(0, size))
            {
                ret[i] = new SortedDictionary<int, T>();
            }
            return ret;
        }
        class RandomChecker
        {
            int[] tree;
            int sz;
            static int GetSize(int s)
            {
                if ((s & -s) == s)
                {
                    return s;
                }
                while ((s & -s) != s)
                {
                    s -= s & -s;
                }
                return s << 1;
            }
            public RandomChecker(int size)
            {
                this.sz = GetSize(size);
                this.tree = new int[2 * this.sz];
            }
            public bool this[int index]
            {
                get
                {
                    return this.tree[index + this.sz] == 1;
                }
                set
                {
                    this.tree[index + this.sz] = value ? 1 : 0;
                    for (var s = (index + this.sz) / 2; s > 0; s /= 2)
                    {
                        this.tree[s] = this.tree[2 * s] + this.tree[2 * s + 1];
                    }
                }
            }
            public int RandomGet()
            {
                if (this.tree[1] == 0)
                {
                    throw new InvalidOperationException("All array is false");
                }
                int RandomGetImpl(int i, int s)
                {
                    if (s == this.sz)
                    {
                        return i;
                    }
                    if (Random.Coin(this.tree[i + s], this.tree[2 * (i + s)]))
                    {
                        return RandomGetImpl(2 * i, s << 1);
                    }
                    else
                    {
                        return RandomGetImpl(2 * i + 1, s << 1);
                    }
                }
                return RandomGetImpl(0, 1);
            }
        }
        static SortedDictionary<int, T>[] TransformWeighted<T>(SortedSet<int>[] graph, Func<T> func)
        {
            var ret = MakeDefaultWeightedGraph<T>(graph.Length);
            foreach (var i in Range(0, graph.Length))
            {
                foreach (var e in graph[i])
                {
                    if (i < e)
                    {
                        break;
                    }
                    ret[i][e] = ret[e][i] = func();
                }
            }
            return ret;
        }
        /// <summary>
        /// Graph to String (Competitive Input Style)
        /// </summary>
        /// <param name="graph">Graph to output</param>
        /// <returns>Graph Data</returns>
        public static string GraphString(SortedSet<int>[] graph)
        {
            var builder = new StringBuilder();
            var edge = 0;
            builder.AppendLine("{0} {1}");
            foreach (var i in Range(0, graph.Length))
            {
                foreach (var j in graph[i].SkipWhile(v => v < i))
                {
                    builder.AppendLine($"{i + 1} {j + 1}");
                    ++edge;
                }
            }
            builder.Replace("{0}", graph.Length.ToString());
            builder.Replace("{1}", edge.ToString());
            return builder.ToString();
        }
        /// <summary>
        /// Graph to String (Competitive Input Style)
        /// </summary>
        /// <typeparam name="T">Weight Type</typeparam>
        /// <param name="graph">Graph to output</param>
        /// <returns>Graph Data</returns>
        public static string GraphString<T>(SortedDictionary<int, T>[] graph)
        {
            var builder = new StringBuilder();
            var size = graph.Length;
            var edge = 0;
            builder.AppendLine("{0} {1}");
            foreach(var i in Range(0, size))
            {
                foreach(var p in graph[i].SkipWhile(p => p.Key < i))
                {
                    var j = p.Key;
                    var v = p.Value;
                    builder.AppendLine($"{i + 1} {j + 1} {v}");
                    ++edge;
                }
            }
            builder.Replace("{0}", size.ToString());
            builder.Replace("{1}", edge.ToString());
            return builder.ToString();
        }
        class GraphMaker
        {
            SortedSet<int>[] graph;
            readonly int size;
            RandomChecker checker;
            readonly int maxDegree;
            int edgeCount;
            public GraphMaker(int size, int maxDegree)
            {
                if (size < 1)
                {
                    throw new ArgumentException("it is impossible to make size 0 graph");
                }
                this.graph = MakeDefaultGraph(size);
                this.size = size;
                this.checker = new RandomChecker(size);
                this.maxDegree = maxDegree;
                this.edgeCount = 0;
            }
            void ConnectionCheck()
            {
                if (this.maxDegree == 0 && this.size > 1)
                {
                    throw new ArgumentException($"it is impossible to make size {this.size} graph whose max degree is 0");
                }
                else if (this.maxDegree == 1 && this.size > 2)
                {
                    throw new ArgumentException($"it is impossible to make size {this.size} graph whose max degree is 1");
                }
            }
            void Connect(int i, int j)
            {
                this.graph[i].Add(j);
                this.graph[j].Add(i);
                if (this.graph[i].Count == this.maxDegree)
                {
                    this.checker[i] = false;
                }
                if (this.graph[j].Count == this.maxDegree)
                {
                    this.checker[j] = false;
                }
                ++this.edgeCount;
            }
            public void MakeTree()
            {
                ConnectionCheck();
                var index = Range(0, this.size).ToList();
                foreach (var i in Range(0, this.size - 1))
                {
                    var j = Random.Next(i, this.size - 1);
                    var c = index[i];
                    index[i] = index[j];
                    index[j] = c;
                }
                this.checker[index[0]] = true;
                foreach (var i in Range(1, this.size - 1))
                {
                    Connect(this.checker.RandomGet(), index[i]);
                    this.checker[index[i]] = true;
                }
            }
            public void MakeGraph(int edgeCount)
            {
                if (this.size * this.maxDegree / 2 < edgeCount)
                {
                    throw new ArgumentOutOfRangeException($"it is impossible to make graph that have {edgeCount} edges, have {this.size} vertexes and max degree is {this.maxDegree}");
                }
                if (this.edgeCount == 0)
                {
                    MakeTree();
                }
                while (edgeCount != this.edgeCount)
                {
                    int a, b;
                    do
                    {
                        a = this.checker.RandomGet();
                        b = this.checker.RandomGet();
                    } while (a == b || this.graph[a].Contains(b));
                    Connect(a, b);
                }
            }

            public SortedSet<int>[] Graph => this.graph;
        }
        /// <summary>
        /// Make Random Tree with N vertexes
        /// </summary>
        /// <param name="N">Vertex Count</param>
        /// <param name="maxDegree">Max Degree</param>
        /// <returns>Tree with N vertexes</returns>
        public static SortedSet<int>[] RandomTree(int N, int maxDegree = int.MaxValue)
        {
            var maker = new GraphMaker(N, Math.Min(N - 1, maxDegree));
            maker.MakeTree();
            return maker.Graph;
        }
        /// <summary>
        /// Make Random Weighted Tree with N vertexes
        /// </summary>
        /// <param name="N">Vertex Count</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <param name="maxDegree">Max Degree</param>
        /// <returns>Weighted Tree with N vertexes</returns>
        public static SortedDictionary<int, int>[] RandomWeightedTree(int N, int minValue, int maxValue, int maxDegree = int.MaxValue)
        {
            return TransformWeighted(RandomTree(N, maxDegree), () => Random.Next(minValue, maxValue));
        }
        /// <summary>
        /// Make Random Weighted Tree with N vertexes
        /// </summary>
        /// <param name="N">Vertex Count</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <param name="maxDegree">Max Degree</param>
        /// <returns>Weighted Tree with N vertexes</returns>
        public static SortedDictionary<int, long>[] RandomWeightedTree(int N, long minValue, long maxValue, int maxDegree = int.MaxValue)
        {
            return TransformWeighted(RandomTree(N, maxDegree), () => (long)Random.Next((int)minValue, (int)maxValue));
        }
        /// <summary>
        /// Make Random Connected Graph with N vertexes and E edges
        /// </summary>
        /// <param name="N">Vertex Count</param>
        /// <param name="E">Edge Count</param>
        /// <param name="maxDegree">Max Degree</param>
        /// <returns>Connected Graph with N vertexes and E edges</returns>
        public static SortedSet<int>[] RandomGraph(int N, int E, int maxDegree = int.MaxValue)
        {
            var maker = new GraphMaker(N, Math.Min(N - 1, maxDegree));
            E = Math.Max(E, N - 1);
            maker.MakeGraph(E);
            return maker.Graph;
        }
        /// <summary>
        /// Make Random Weighted Connected Graph with N vertexes and E edges
        /// </summary>
        /// <param name="N">Vertex Count</param>
        /// <param name="E">Edge Count</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <param name="maxDegree">Max Degree</param>
        /// <returns>Weighted Connected Graph with N vertexes and E edges</returns>
        public static SortedDictionary<int, int>[] RandomWeightedGraph(int N, int E, int minValue, int maxValue, int maxDegree = int.MaxValue)
        {
            return TransformWeighted(RandomGraph(N, E, maxDegree), () => Random.Next(minValue, maxValue));
        }
        /// <summary>
        /// Make Random Weighted Connected Graph with N vertexes and E edges
        /// </summary>
        /// <param name="N">Vertex Count</param>
        /// <param name="E">Edge Count</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <param name="maxDegree">Max Degree</param>
        /// <returns>Weighted Connected Graph with N vertexes and E edges</returns>
        public static SortedDictionary<int, long>[] RandomWeightedGraph(int N, int E, long minValue, long maxValue, int maxDegree = int.MaxValue)
        {
            return TransformWeighted(RandomGraph(N, E, maxDegree), () => (long)Random.Next((int)minValue, (int)maxValue));
        }

    }
}
