﻿using System;
using System.Collections.Generic;
using System.Text;
using static System.Linq.Enumerable;
using static Codeforces.IO;

namespace Codeforces
{
    static class IO
    {
        static StringBuilder builder = new StringBuilder();
        private class Dummy
        {
            ~Dummy()
            {
                Flush();
            }
        }
        static Dummy dummy = new Dummy();
        public static void Write(object obj)
        {
            builder.Append(obj);
        }
        static IEnumerable<T> Iterate<T>(T[,] ts, int i, int s)
        {
            foreach (var j in Range(0, s))
            {
                yield return ts[i, j];
            }
        }
        public static void WriteLine<T>(IEnumerable<T> ts)
        {
            var ite = ts.GetEnumerator();
            if (ite.MoveNext())
            {
                Write(ite.Current);
                while (ite.MoveNext())
                {
                    Write(" ");
                    builder.Append(ite.Current);
                }
                builder.AppendLine();
            }
        }
        public static void WriteLine<T>(T[,] ts)
        {
            var (s0, s1) = (ts.GetLength(0), ts.GetLength(1));
            foreach (var i in Range(0, s0))
            {
                WriteLine(Iterate(ts, i, s1));
            }
        }
        public static void WriteLine(object v)
        {
            Write(v);
            builder.AppendLine();
        }
        public static void WriteLine<T0, T1>(T0 v0, T1 v1)
        {
            Write(v0);
            Write(" ");
            Write(v1);
            builder.AppendLine();
        }
        public static void WriteLine<T0, T1, T2>(T0 v0, T1 v1, T2 v2)
        {
            Write(v0);
            Write(" ");
            Write(v1);
            Write(" ");
            Write(v2);
            builder.AppendLine();
        }
        public static void Flush()
        {
            Console.Write(builder.ToString());
            builder.Clear();
        }
        public static T[] ReadArray<T>(Func<string, T> parser)
        {
            return Console.ReadLine().Split(' ').Select(parser).ToArray();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            WriteLine(ReadArray(int.Parse));
        }
    }
}