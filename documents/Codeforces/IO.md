# static class IO
基本的な標準出力関数及び特殊な標準入力関数を提供する。  
namespace Codeforcesに含まれている。   
このクラスはsubmit用ファイルに含まれており、標準出力へはこのクラスの関数を通じて出力されることを前提に設計されている。  
また初期状態ではusing staticされている。
## このクラスの出力関数について
このクラスの出力関数では出力用文字列のバッファのみを行う。  
実際に出力されるのはFlush()が呼ばれた時かプログラムの終了時である。
## public static void Write(object obj)
objの中身を出力する。
### 使用例
```csharp
static void Main(string[] args)
{
    Write(1);
}
```
---
## public static void WriteLine\<T\>(IEnumerable\<T\> ts)
tsの要素を空白区切りに一行に出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = new int[] { 1, 2, 3 };
    WriteLine(ar);
}
```
---
## public static void WriteLine\<T\>(T[,] ts)
tsがnew T[n, m]で初期化されている場合、n行に渡りtsの要素を空白区切りに出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    var ar = new int[,]
    {
        {1,2,3 },
        {4,5,6 }
    };
    WriteLine(ar);
}
```
---
## public static void WriteLine(object v)
vを出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(1);
}
```
---
## public static void WriteLine\<T0, T1\>(T0 v0, T1 v1)
v0とv1を空白区切りで出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(1, 2);
}
```
---
## public static void WriteLine\<T0, T1, T2\>(T0 v0, T1 v1, T2 v2)
v0とv1とv2を空白区切りで出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(1, 2, 3);
}
```
---
## public static void Flush()
バッファしている文字列を出力する。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(1);
    Flush();
}
```
---
## public static T[] ReadArray\<T\>(Func\<string, T\> parser)
標準入力から一行受け取り、空白で区切った後、各文字列にparserを適用した配列を返す。
### 使用例
```csharp
static void Main(string[] args)
{
    WriteLine(ReadArray(int.Parse));
}
```
---
## このクラスが必要になった背景
ナイーブにSystem.Console.Writeを利用し、出力のみでTLEになることがあったからである。  
具体的にはCodeforces Round #545 (Div. 2) C. Skyscrapersで起こった。以下の2つのsubmitを比較するとわかりやすい。  
http://codeforces.com/contest/1138/submission/53465870  
http://codeforces.com/contest/1138/submission/53466399