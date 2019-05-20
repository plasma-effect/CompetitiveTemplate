# main.cppについて
int main()関数内ではstd::cinとstd::coutの前処理を行い、本質的な実装はvoid Main()関数内で行うようにしている。これは
- main関数内である場合return文にはint型の数値が必要でその記述が面倒
- Cスタイルの出力関数との同期を切ることで入出力を高速化
- 浮動小数点数が必ず小数値で表されるようにする

などの理由がある。  
以下のライブラリの使用例ではvoid Main()関数内に記述する形で使用例を示すことにする。  
# [debug_print.hpp](./debug_print.md)
printfデバッグ用の関数が提供される。
# [random.hpp](./random.md)
基本的な乱数生成用の関数オブジェクトが提供される。
# [graph.hpp](./graph.md)
単純無向グラフのランダム生成、及び出力関数が提供される。