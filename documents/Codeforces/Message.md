# static class Message
標準エラー出力利用補助の関数を提供する。  
このクラスはnamespace Codeforces.Debugに含まれている。
## このクラスの出力関数について
このクラスの出力関数では標準エラー出力に出力される。  
このクラスで提供される関数はFlush()とReadArray()がないことを除きstatic class IOと同一である。
## public static void Write(object obj)
objの中身を出力する。
### 使用例
```csharp
static void Main(string[] args)
{
    Debug.Message.Write(1);
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
    Debug.Message.WriteLine(ar);
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
    Debug.Message.WriteLine(ar);
}
```
---
## public static void WriteLine(string str)
strを出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    Debug.Log.WriteLine("Test");
}
```
---
## public static void WriteLine(object v)
vを出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    Debug.Message.WriteLine(1);
}
```
---
## public static void WriteLine\<T0, T1\>(T0 v0, T1 v1)
v0とv1を空白区切りで出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    Debug.Message.WriteLine(1, 2);
}
```
---
## public static void WriteLine\<T0, T1, T2\>(T0 v0, T1 v1, T2 v2)
v0とv1とv2を空白区切りで出力し、改行する。
### 使用例
```csharp
static void Main(string[] args)
{
    Debug.Message.WriteLine(1, 2, 3);
}
```