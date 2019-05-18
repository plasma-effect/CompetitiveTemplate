# CompetitiveTemplate
「普段使ってる競プロ用プロジェクトをpublicにしてもいいのでは？」と思った。  
現在はAtCoderにのみ対応、そのうちCodeforces用のC#verも作りたい。
# 使い方
- VS2019でAtCoderのソリューションを開く。
- main.cppに色々書き書きする。
- ビルドか保存をする。
- main.cppをsubmitする。
# boostについて
Nugetで管理しているのでビルドが必要なライブラリが使えません。
# ライセンスについて
- main.cppのみパブリックドメイン。
- それ以外はMITライセンス。
# デバッグ用関数及びクラスについて
- bits/stdc++.h内でincludeしているため、使用した場合削除せずsubmitするとジャッジサーバー内でコンパイルエラーになる。
- 提供している関数とクラスについては[こちら](./documents/index.md)。