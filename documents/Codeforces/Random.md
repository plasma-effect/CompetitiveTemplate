# static class Random
乱数生成関数を提供する。  
このクラスはnamespace Codeforces.Debugに含まれている。
## public static int Next()
0以上のランダムな数を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(Debug.Random.Next());
}
```
---
## public static int Next(int maxValue)
0以上maxValue以下のランダムな数を返す。  
System.Random.Nextと違いmaxValueを含むことに注意(以下の関数でも同様)。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(Debug.Random.Next(10));
}
```
---
## public static int Next(int minValue, int maxValue)
minValue以上maxValue以下のランダムな数を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(Debug.Random.Next(-5, 5));
}
```
---
## public static bool Coin(int denominator, int numerator)
numerator/denominatorの確率でtrue、そうでないときfalseを返す。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(Debug.Random.Coin(3, 2));
}
```
---
## public static int[] RandomArray(int length, int minValue, int maxValue)
minValue以上maxValue以下のランダムな数で構成された、長さlengthのint型配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomArray(5, -5, 5);
    WriteLine(ar);
}
```
---
## public static int[] RandomArray(int length, int maxValue)
0以上maxValue以下のランダムな数で構成された、長さlengthのint型配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomArray(5, 5);
    WriteLine(ar);
}
```
---
## public static long[] RandomArray(int length, long minValue, long maxValue)
minValue以上maxValue以下のランダムな数で構成された、長さlengthのlong型配列を返す。  
引数の型でオーバーロードしていることに注意せよ。  
またSystem.Randomを内部で利用している都合上
- minValueはint.MinValue以上
- maxValueはint.MaxValue未満

でなくてはならない(以下のlong型の関数も同様)。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomArray(5, -5L, 5L);
    WriteLine(ar);
}
```
---
## public static long[] RandomArray(int length, long maxValue)
0L以上maxValue以下のランダムな数で構成された、長さlengthのlong型配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomArray(5, 5L);
    WriteLine(ar);
}
```
---
## public static int[,] RandomDualArray(int H, int W, int minValue, int maxValue)
minValue以上maxValue以下のランダムな数で構成された、new int[H, W]で初期化されたint型二次配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomDualArray(3, 3, -5, 5);
    WriteLine(ar);
}
```
---
## public static int[,] RandomDualArray(int H, int W, int maxValue)
0以上maxValue以下のランダムな数で構成された、new int[H, W]で初期化されたint型二次配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomDualArray(3, 3, 5);
    WriteLine(ar);
}
```
---
## public static long[,] RandomDualArray(int H, int W, long minValue, long maxValue)
minValue以上maxValue以下のランダムな数で構成された、new int[H, W]で初期化されたlong型二次配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomDualArray(3, 3, -3L, 3L);
    WriteLine(ar);
}
```
---
## public static long[,] RandomDualArray(int H, int W, long maxValue)
0L以上maxValue以下のランダムな数で構成された、new int[H, W]で初期化されたlong型二次配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = Debug.Random.RandomDualArray(3, 3, 5L);
    WriteLine(ar);
}
```