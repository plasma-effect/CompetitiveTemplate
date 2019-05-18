# random.hpp
乱数生成関数を提供する。一部の関数は関数オブジェクトとして提供されている。  
全てnamespace debug::random内に含まれている。
# 提供している関数オブジェクト
## constexpr \<type\> next, coin
「乱数生成をする関数オブジェクト」を返すoperator()を関数メンバとして持つ関数オブジェクト。operator()の返り値の関数オブジェクトは次のような特性を持つ。
- operator()はその場で生成した乱数を返す。
- 型Tにキャストした時
    - まだ一度もキャストしていない場合乱数を生成しその値を返す。
    - すでに一回以上キャストしている場合前回の値を返す。
---
## template\<class T\> auto next(T min, T max)
「min以上max以下の値を返す」乱数生成関数オブジェクトを返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	std::cout << next(1, 5) << std::endl << std::endl;

	auto f = next(1, 5);
	for (int i : boost::irange(0, 5))
	{
		std::cout << f() << std::endl;
	}
}
```
---
## template\<class T\> auto next(T max)
「0以上max以下の値を返す」乱数生成関数オブジェクトを返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	std::cout << next(5) << std::endl << std::endl;

	auto f = next(5);
	for (int i : boost::irange(0, 5))
	{
		std::cout << f() << std::endl;
	}
}
```
---
## auto next()
「std::int64_tになりうる全ての値のいずれかを返す」乱数生成関数オブジェクトを返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	std::cout << next() << std::endl << std::endl;

	auto f = next();
	for (int i : boost::irange(0, 5))
	{
		std::cout << f() << std::endl;
	}
}
```
---
## auto coin(std::size_t denominator, std::size_t numerator)
「確率numerator/denominatorでtrue、それ以外の場合falseを返す」乱数生成関数オブジェクトを返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	std::cout << std::boolalpha << coin(5, 2) << std::endl << std::endl;

	auto f = coin(5, 2);
	for (int i : boost::irange(0, 5))
	{
		std::cout << f() << std::endl;
	}
}
```
---
## auto coin(double p)
「確率pでtrue、それ以外の場合falseを返す」乱数生成関数オブジェクトを返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	std::cout << std::boolalpha << coin(0.3) << std::endl << std::endl;

	auto f = coin(0.3);
	for (int i : boost::irange(0, 5))
	{
		std::cout << f() << std::endl;
	}
}
```
---
# 提供しているtemplate関数
## template\<class T\>auto random_vector(std::size_t size, T min, T max)
各要素がmin以上max以下の数であるサイズがsizeのvectorを返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	auto vec = random_vector(5, 1, 5);
	for (auto&& v : vec)
	{
		std::cout << v << std::endl;
	}
}
```cpp

```
---
## template\<class T\>auto random_vector(std::size_t size, T max)
各要素が0以上max以下の数であるサイズがsizeのvectorを返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	auto vec = random_vector(5, 5);
	for (auto&& v : vec)
	{
		std::cout << v << std::endl;
	}
}
```
---
## template\<class T\>auto random_dual_array(std::size_t H, std::size_t W, T min, T max)
各要素がmin以上max以下である、boost::extents\[H\]\[W\]で初期化されたboost::multi_array\<T, 2\>を返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	auto ar = random_dual_array(3, 3, 1, 5);
	for (int i : boost::irange(0, 3))
	{
		for (int j : boost::irange(0, 3))
		{
			std::cout << ar[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
```
---
## template\<class T\>auto random_dual_array(std::size_t H, std::size_t W, T max)
各要素が0以上max以下である、boost::extents\[H\]\[W\]で初期化されたboost::multi_array\<T, 2\>を返す。
### 使用例
```cpp
void Main()
{
	using namespace debug::random;
	auto ar = random_dual_array(3, 3, 5);
	for (int i : boost::irange(0, 3))
	{
		for (int j : boost::irange(0, 3))
		{
			std::cout << ar[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
```