# 草

## 命令一覧

| 命令 | 引数(有・無) | 仕様 |
| ---- | ---- | ---- |
| WWW | 有 | 整数値をスタックに積む |
| WWw | 有 | (引数)番目のスタックを複製し一番上に積む |
| WWv | 無 | 一番上のスタックを複製 |
| WWV | 無 | スタックを交換 |
| WVv | 無 | 一番上のスタックを破棄 |
| WVV | 有 | 上から(引数)個のスタックを破棄 |
| Wwv | 無 | スタックをランダムに並び替える |
| www | 無 | 上二つのスタックを足してスタックに積む |
| wwv | 無 | 二番目のスタックから一番上のスタックを引いてスタックに積む |
| wvv | 無 | 上二つのスタックを掛けてスタックに積む |
| wvw | 無 | 二番目のスタックを一番上のスタックで割ってスタックに積む |
| wvW | 無 | 二番目のスタックを一番上のスタックで割った余りをスタックに積む |
| vVv | 無 | ヒープ(一番上のスタックの値がアドレス)に二番目のスタックの値を書き込む |
| vVV | 無 | ヒープ(一番上のスタックの値がアドレス)の値をスタックに積む |
| vvv | 無 | 一番上のスタックの値=文字コードに対応する文字を出力|
| vvw | 無 | 一番上のスタックの値を出力 |
| vwv | 無 | **一文字**を読み取りその文字コードをスタックに積む |
| vww | 無 | **一行**を読み取りその数字をスタックに積む |
| wVw | 有 | ラベルとその番号(引数)を設定する |
| wWw | 有 | 指定したラベルにジャンプする |
| wWv | 有 | 一番上のスタックの値が0なら指定したラベルにジャンプする |
| wWV | 有 | 一番上のスタックの値が負の数なら指定したラベルにジャンプする |
| wVv | 有 | 現在の位置をコールスタックに積んで指定したラベルにジャンプする |
| wVV | 無 | 「コールスタックの一番上」の位置に戻る |
| V | 無 | 引数終了 |
| VV | 無 | プログラム終了 |

## 文法

- Whitespaceと同じような感じ
- 引数は二進数表記(w=0,v=1)

## スタックの番号
```
上
-------
|  n  |
-------
|  :  |
-------
|  2  |
-------
|  1  |
-------
|  0  |
-------
下
```

## Hello world
```
WWWwvwwvwwwVWWWwvvwwvwvVWWWwvv
wvvwwVWWW  wvvwvvww  VWWWwvvwv
vvv                        VWW
WwvwwwwwV  WWWwvvvw  vvvVWWWwv
vwvvvv                  VWWWwv
vvwwvw   VWWWwvvwvvww   VWWWwv
vwwvww                  VWWWwv
wwwwvV   WWWwvvwvwwww   vwvwVW
WWwVWW                  WwVvVv
wVwwVWWWwVvVVW   WvWWWwvvwvVww
vwWvwvVWWWwvVW   WVwwwWWvWWWwV
vV                          vv
VvwWwwVwVwwvVW   WWwVvVVWWvwWv
wvwVWWvvVVvvvW   WWwvVwwvWWWwV
vVvwWwwvVwVwwvwVVVVVVVVVVVVVVV

```
