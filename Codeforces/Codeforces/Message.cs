//This source code is under the MIT License, see LICENSE.txt.
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using static System.Linq.Enumerable;

namespace Codeforces.Debug
{
    static class Message
    {
        /// <summary>
        /// Write obj
        /// </summary>
        /// <param name="obj">Value to write</param>
        public static void Write(object obj)
        {
            Console.Error.Write(obj);
        }
        /// <summary>
        /// Terminate this line
        /// </summary>
        public static void WriteLine()
        {
            Console.Error.WriteLine();
        }
        /// <summary>
        /// Write elements of ts with blank delimiter and Terminate this line
        /// </summary>
        /// <typeparam name="T">Type Parameter</typeparam>
        /// <param name="ts">Enumerable Object to write</param>
        public static void WriteLine<T>(IEnumerable<T> ts)
        {
            var ite = ts.GetEnumerator();
            if (ite.MoveNext())
            {
                Write(ite.Current);
                while (ite.MoveNext())
                {
                    Write(" ");
                    Write(ite.Current);
                }
            }
            WriteLine();
        }
        /// <summary>
        /// Write elements of ts with blank delimiter
        /// </summary>
        /// <typeparam name="T">Type Parameter</typeparam>
        /// <param name="ts">Dual Array to write</param>
        public static void WriteLine<T>(T[,] ts)
        {
            var (s0, s1) = (ts.GetLength(0), ts.GetLength(1));
            foreach (var i in Range(0, s0))
            {
                WriteLine(Range(0, s1).Select(j => ts[i, j]));
            }
        }
        /// <summary>
        /// Write str and Terminate this line
        /// </summary>
        /// <param name="str">String to write</param>
        public static void WriteLine(string str)
        {
            Write(str);
            WriteLine();
        }
        /// <summary>
        /// Write obj and Terminate this line
        /// </summary>
        /// <param name="obj">Object to write</param>
        public static void WriteLine(object obj)
        {
            Write(obj);
            WriteLine();
        }
        /// <summary>
        /// Write v0 and v1 with blank delimiter and Terminate this line
        /// </summary>
        /// <typeparam name="T0">Type Parameter</typeparam>
        /// <typeparam name="T1">Type Parameter</typeparam>
        /// <param name="v0">First value to write</param>
        /// <param name="v1">Second value to write</param>
        public static void WriteLine<T0, T1>(T0 v0, T1 v1)
        {
            Write(v0);
            Write(" ");
            Write(v1);
            WriteLine();
        }
        /// <summary>
        /// Write v0, v1 and v2 with blank delimiter and Terminate this line
        /// </summary>
        /// <typeparam name="T0">Type Parameter</typeparam>
        /// <typeparam name="T1">Type Parameter</typeparam>
        /// <typeparam name="T2">Type Parameter</typeparam>
        /// <param name="v0">First value to write</param>
        /// <param name="v1">Second value to write</param>
        /// <param name="v2">Third value to write</param>
        public static void WriteLine<T0, T1, T2>(T0 v0, T1 v1, T2 v2)
        {
            Write(v0);
            Write(" ");
            Write(v1);
            Write(" ");
            Write(v2);
            WriteLine();
        }
    }
}
