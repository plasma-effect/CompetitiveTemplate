//This source code is under the MIT License, see LICENSE.txt.
using static System.Linq.Enumerable;
namespace Codeforces.Debug
{
    static class Random
    {
        static System.Random random = new System.Random();
        /// <summary>
        /// Return random number more than or equal to 0
        /// </summary>
        /// <returns>random number</returns>
        public static int Next()
        {
            return random.Next();
        }
        /// <summary>
        /// Return random number in [0, maxValue](include maxValue)
        /// </summary>
        /// <param name="maxValue">Max Value</param>
        /// <returns>random number(in [0, maxValue])</returns>
        public static int Next(int maxValue)
        {
            return random.Next(maxValue + 1);
        }
        /// <summary>
        /// Return random number in [minValue, maxValue](include maxValue)
        /// </summary>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>random number(in [minValue, maxValue])</returns>
        public static int Next(int minValue, int maxValue)
        {
            return random.Next(minValue, maxValue + 1);
        }
        /// <summary>
        /// Make array that is made by random numbers in [minValue, maxValue](include maxValue)
        /// </summary>
        /// <param name="length">Array Length</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static int[] RandomArray(int length, int minValue, int maxValue)
        {
            var ret = new int[length];
            foreach(var i in Range(0, length))
            {
                ret[i] = Next(minValue, maxValue);
            }
            return ret;
        }
        /// <summary>
        /// Make array that is made by random numbers in [0, maxValue](include maxValue)
        /// </summary>
        /// <param name="length">Array Length</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static int[] RandomArray(int length, int maxValue)
        {
            return RandomArray(length, 0, maxValue);
        }
        /// <summary>
        /// Make array that is made by random numbers in [minValue, maxValue](include maxValue)
        /// </summary>
        /// <param name="length">Array Length</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static long[] RandomArray(int length, long minValue, long maxValue)
        {
            var ret = new long[length];
            if (minValue < int.MinValue || int.MaxValue <= maxValue)
            {
                throw new System.ArgumentOutOfRangeException($"It is impossible to make array that is made by numbers in [{minValue}, {maxValue}]");
            }
            foreach(var i in Range(0, length))
            {
                ret[i] = Next((int)minValue, (int)maxValue);
            }
            return ret;
        }
        /// <summary>
        /// Make array that is made by random numbers in [0, maxValue](include maxValue)
        /// </summary>
        /// <param name="length">Array Length</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static long[] RandomArray(int length, long maxValue)
        {
            return RandomArray(length, 0L, maxValue);
        }
        /// <summary>
        /// Make dual array that is made by random numbers in [minValue, maxValue](include maxValue)
        /// </summary>
        /// <param name="H">Dimention 0 Size</param>
        /// <param name="W">Dimention 1 Size</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static int[,] RandomDualArray(int H, int W, int minValue, int maxValue)
        {
            var ret = new int[H, W];
            foreach(var i in Range(0, H))
            {
                foreach(var j in Range(0, W))
                {
                    ret[i, j] = Next(minValue, maxValue);
                }
            }
            return ret;
        }
        /// <summary>
        /// Make dual array that is made by random numbers in [0, maxValue](include maxValue)
        /// </summary>
        /// <param name="H">Dimention 0 Size</param>
        /// <param name="W">Dimention 1 Size</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static int[,] RandomDualArray(int H, int W, int maxValue)
        {
            return RandomDualArray(H, W, 0, maxValue);
        }
        /// <summary>
        /// Make dual array that is made by random numbers in [minValue, maxValue](include maxValue)
        /// </summary>
        /// <param name="H">Dimention 0 Size</param>
        /// <param name="W">Dimention 1 Size</param>
        /// <param name="minValue">Min Value</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static long[,] RandomDualArray(int H, int W, long minValue, long maxValue)
        {
            if (minValue < int.MinValue || int.MaxValue <= maxValue)
            {
                throw new System.ArgumentOutOfRangeException($"It is impossible to make dual array that is made by numbers in [{minValue}, {maxValue}]");
            }
            var ret = new long[H, W];
            foreach (var i in Range(0, H))
            {
                foreach (var j in Range(0, W))
                {
                    ret[i, j] = Next((int)minValue, (int)maxValue);
                }
            }
            return ret;
        }
        /// <summary>
        /// Make dual array that is made by random numbers in [0, maxValue](include maxValue)
        /// </summary>
        /// <param name="H">Dimention 0 Size</param>
        /// <param name="W">Dimention 1 Size</param>
        /// <param name="maxValue">Max Value</param>
        /// <returns>Randomized Array</returns>
        public static long[,] RandomDualArray(int H, int W, long maxValue)
        {
            return RandomDualArray(H, W, 0L, maxValue);
        }
    }
}
