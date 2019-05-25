//This source code is under the MIT License, see LICENSE.txt.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Linq.Enumerable;

namespace Codeforces.Debug.Detail
{
    static class Utility
    {
        public static T[] MakeArray<T>(int size)
            where T : class, new()
        {
            var ret = new T[size];
            foreach(var i in Range(0, size))
            {
                ret[i] = new T();
            }
            return ret;
        }
    }
}
