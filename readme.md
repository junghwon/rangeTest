# RangeTest

## ビルド方法
ターミナルにて下記を実行する。
```shell
$ make
```
makeが使えない場合は以下を実行する。
```shell
$ gcc -o rangeTest main.c rangeController.c rangeKeyController.c rangeCookModel.c rangeMagnetronModel.c rangeRelayModel.c rangeTimer_Model.c rangeView.c -lpthread
```
<br>

## 操作方法
* 調理時間設定

    キーボードで't'を入力する度に、以下の通り調理時間が変更される。<br>
    0秒 → 10秒 → 20秒 → 30秒 → 40秒 → 50秒 → 60秒 → 0秒...<br>
    ※初期値：0秒
<br>

* 調理出力設定

    キーボードで'w'を入力する度に、以下の通り出力が変更される。<br>
    500w → 400w → 300w → 200w → 100w → 500w...<br>
    ※初期値：500w
<br>

* 調理開始

    キーボードで's'を入力すると、調理が開始される。<br>
<br>

## マグネトロン駆動時間
電子レンジ出力設定によって、以下の通りマグネトロンの出力時間が設定される。<br>
* 500w ： 9秒ON、1秒OFF
* 400w ： 7秒ON、3秒OFF
* 300w ： 5秒ON、5秒OFF
* 200w ： 3秒ON、7秒OFF
* 100w ： 1秒ON、9秒OFF

