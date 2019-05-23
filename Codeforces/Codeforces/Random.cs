//This source code is under the MIT License, see LICENSE.txt.
namespace Codeforces
{
    namespace Debug
    {
        static class Random
        {
            static System.Random random = new System.Random();
            /// <summary>
            /// return random number more than or equal to 0
            /// </summary>
            /// <returns>random number</returns>
            public static int Next()
            {
                return random.Next();
            }
            /// <summary>
            /// return random number in [0, maxValue](include maxValue)
            /// </summary>
            /// <param name="maxValue">Max Value</param>
            /// <returns>random number(in [0, maxValue])</returns>
            public static int Next(int maxValue)
            {
                return random.Next(maxValue + 1);
            }
            /// <summary>
            /// return random number in [minValue, maxValue](include maxValue)
            /// </summary>
            /// <param name="minValue">Min Value</param>
            /// <param name="maxValue">Max Value</param>
            /// <returns>random number(in [minValue, maxValue])</returns>
            public static int Next(int minValue,int maxValue)
            {
                return random.Next(minValue, maxValue);
            }
        }
    }
}
