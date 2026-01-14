# RangeTest

## ビルド方法
### CMakeによるビルド
ターミナルにて下記を実行する。
```shell
$ mkdir BUILD
$ cd BUILD
$ cmake ../CMakeLists.txt
$ make
```
### makeによるビルド
ターミナルにて下記を実行する。
```shell
$ make
```
### CMake、makeが使えない場合のビルド
ターミナルにて下記を実行する。
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

## クラス図
    range_class_diagram.pdfを参照。
<br>

## MVCモデル
    本プログラムはMVCモデルパターンに沿って作成されている。
    電子レンジ動作のロジックを担当するModel、
    表示に関する処理を担当するView、
    ユーザー入力及び、ModelとViewに対する制御を担当するControllerから成る。

    以下に各クラスとM、V、Cそれぞれの対応を記載する。
    ・Model：rangeCookModel, rangeMagnetronModel, rangeRelayModel, rangeTimerModel
    ・View：rangeView
    ・Controller：rangeController, rangeKeyController
<br>

## 各クラスの役割
### rangeController
    主にユーザーから見える設定、操作を行う。
    属性
    ・watt          …　電子レンジ出力設定値
    ・timer         …　調理時間設定値
    操作
    ・startup       …　起動処理を行う。
    ・wattSetting   …　電子レンジの出力を設定する。
    ・timerSetting  …　調理時間を設定する。
    ・start         …　調理を開始する。
    ・stop          …　調理完了時の処理。
    ・manager       …　調理工程制御(rangeCookModel)を呼び出す。

### rangeKeyController
    キーボード入力を制御する。
    属性
    ・keyCode       …　入力されたキーコードの値
    操作
    ・scanKey      …　キーボードの入力監視を行う。
    ・getKey       …　キーコードを取得する。

### rangeView
    表示の制御を行う。
    属性
    ・なし
    操作
    ・startUpDisplay    …　起動時の表示を行う。
    ・wattDisplay       …　出力設定時の表示を行う。
    ・timerDisplay      …　調理時間設定時の表示を行う。
    ・startDisplay      …　調理開始時の表示を行う。
    ・stopDisplay       …　調理完了時の表示を行う。
    ・cookTimerDisplay  …　調理中のカウントダウン表示を行う。

### rangeCookModel
    調理工程を制御する。
    属性
    ・state             …　調理工程
    ・cookTimer         …　調理時間（カウント値）
    操作
    ・cookManager       …　調理工程を制御する。以下の状態を持つ。
                                stateStandby：調理スタンバイ
                                stateCook：調理中
                                stateEnd：調理完了
    ・cookStart         …　調理工程を開始する。
    ・getCookTimer      …　調理時間を取得する。

### rangeMagnetronModel
    マグネトロンの駆動を制御する。
    属性
    ・mqOnTime      …　マグネトロンON時間設定値
    ・mqOffTime     …　マグネトロンOFF時間設定値
    ・state         …　マグネトロンON又は、OFFの状態
    ・mqCounter     …　マグネトロンON又は、OFFのカウント値
    操作
    ・manager       …　マグネトロンON、OFF状態を制御する。
    ・init          …　マグネトロン駆動状態を初期化する。
    ・mqStart       …　マグネトロンの駆動時間を設定し、駆動制御を開始する。

### rangeRelayModel
    リレー制御を行う。
    属性
    ・relayState    …　リレーのON、OFF状態
    操作
    ・relayOn       …　リレー状態をONにする。
    ・relayOff      …　リレー状態をOFFにする。

### rangeTimerModel
    制御に関する時間のカウントを行う。
    属性
    ・timer         …　カウント値のアドレス
    ・countEnable   …　カウント許可
    操作
    ・setTimer      …　カウント値に時間をセットする。
    ・initTimer     …　カウント値を初期化する。
    ・countTimer    …　カウントを行う。
<br>


