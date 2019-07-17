# multiResSynthesis
多重解像度の画像合成を行うプログラムです。

# ビルド方法
slnファイルを開いてプロジェクトのプロパティのインクルードディレクトリとリンカーの追加のライブラリディレクトリのパスを適宜合わせてビルドしてください。（要OpenCV）C++17の機能を一部使用しているので、C++言語標準をISO C++17標準にしないとビルドできません。

# 実行方法
実行ファイルを引数なしで実行すると、実行するのに必要な引数リストが出力されます。必要な引数は次の通りです。

- file:入力テクスチャのファイルパス(Ex. *.jpg)
- MultiResLevel:多重解像度処理のレベル数を整数で入力する(Ex. 3)
- DstRes:出力テクスチャの解像度を整数で入力する(Ex. 300)
- Nbr:近傍のサイズを整数で入力する(Ex. 3)

それぞれの引数に正しいパラメータを設定すると画像合成が始まり、実行ファイルと同じ階層にresult というフォルダを作っておくことで、そのフォルダ内に合成結果の画像ファイルと、合成した時間、どのファイルを用いて合成したのか、どのようなパラメータを設定したのか、合成にかかった時間がresult.yml というファイルに出力されます。result.yml は適当なテキストエディタで開いて内容を確認することができます。
