# CompetitiveTemplate
「普段使ってる競プロ用プロジェクトをpublicにしてもいいのでは？」と思った。  
AtCoderとCodeforcesに対応しているが
- AtCoderはC++14&boost
- CodeforcesはC# 7.2

を使用することを想定している。
# 使い方
## AtCoder
- VS2019でAtCoderのソリューションを開く。
- main.cppに色々書き書きする。
- ビルドか保存をする。
- main.cppをsubmitする。
## Codeforces
- VS2019でCodeforcesのソリューションを開く。
- Program.csに色々書き書きする。
- ビルドか保存をする。
- Program.csをsubmitする。
# AtCoderソリューションのboostについて
Nugetで管理しているのでビルドが必要なライブラリが使えません。
# ライセンスについて
- main.cppとProgram.csのみパブリックドメイン。
- それ以外はMITライセンス。
# デバッグ用関数及びクラスについて
- AtCoderソリューションではbits/stdc++.h内でデバッグ用ヘッダをincludeしているため、デバッグ用関数を使用した場合削除せずsubmitするとジャッジサーバー内でコンパイルエラーになる。
- 提供している関数とクラスについては[こちら](./documents/index.md)。