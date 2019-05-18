# debug_print.hpp
printfデバッグ用の出力関数を提供する。  
全てnamespace debug::print内に含まれている。
# 提供している関数
writeとある関数は./debugに出力される。  
messageとある関数とある関数は標準エラー出力に出力される。
## template\<class... Ts\>void write(Ts const& ... vs)
sizeof...(Ts)が0でない場合、空白区切りで一行に出力される。  
sizeof...(Ts)が0である場合、何も行われない。
## template\<class... Ts\>void write_line(Ts const& ... vs)
write(vs...)が呼ばれた後に改行される。
## template\<class Range\>void write_range(Range const& rng)
rngの各要素vに対しwrite_line(v)が呼ばれる。
## template\<class... Ts\>void message(Ts const& ... vs)
sizeof...(Ts)が0でない場合、空白区切りで一行に出力された後改行される。  
sizeof...(Ts)が0である場合、改行のみが行われる。
## template\<class Range\>void message_range(Range const& rng)
rngの各要素vに対しmessage(v)が呼ばれる。
# 対応している型
複数の条件を満たす場合、上にある条件の方が優先される。
## operator\<\<(std::ostream& os, T const& v)がオーバーロードされている型T
次の演算が行われる。
```cpp
os << v
```
## boost::multi_array\<T, 2\>
boost::extents\[H\]\[W\]で初期されている場合、H行W列に渡り空白区切りで出力される。
## range-base forに対応しているコンテナクラス
スペース区切りに一行に出力される。
## std::tuple_size\<T\>::valueが存在する型
スペース区切りに一行に出力される。