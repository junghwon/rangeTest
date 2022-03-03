# C言語でオブジェクト指向を実現する

参考サイト：<br>[初心者向けに徹底解説！オブジェクト指向とは？](https://eng-entrance.com/what-oop)<br>[オブジェクト指向によるクラス設計](https://thinkit.co.jp/article/13112)<br>[MVCモデルについて](https://qiita.com/s_emoto/items/975cc38a3e0de462966a)

## はじめに
    
    各処理をクラス単位のモジュールに分割し、再利用性の高いプログラムを組むことを達成するために
    C言語でオブジェクト指向的にプログラムを設計する事を目標とする。
<br>

## オブジェクト指向でプログラミングする事のメリット
    オブジェクト指向でプログラミングを行う事で以下のようなメリットがあると考える。
    ・クラス単位でモジュール化して実装することができる。
        →多人数での分担実装、単体テストの実施が容易になる。
        →モジュール間の結合度が下がることにより、プログラムの修正や変更が容易になる。
    ・UMLに従ってモデリングできる。
        →プログラム全体を俯瞰して図示できるため、プログラム設計やコードの理解が容易になる。
<br>

## できること、できないこと
    C言語でオブジェクト指向プログラムをどこまで再現するか、出来る事と出来ない事を始めに決める。

### 出来ること
    ・クラス単位でのモジュール化        ：構造体を用いてクラスを表現する。
    ・クラスに属性と操作を持たせる      ：関数ポインタを用いて構造体に操作を実装する。
    ・クラスの集約（集化、has-aの関係） ：クラスメンバに別のクラスを取り込む。
    ・多態性                          ：クラス操作(関数ポインタ)に任意の関数を渡すことで実現する。

### 出来ないこと
    ・クラスの継承（is-aの関係）        ：工夫をすればC言語でも継承を実現できるが、複雑になるため継承は行わない。
    ・カプセル化                       ：C言語仕様上、カプセル化は実装できないので諦める。
<br>


## クラスの実装方法
### クラスの定義
    クラスは構造体（struct）を用いて定義する。
    クラスは以下の3種類のメンバーを持つことができる。
    ・属性（フィールド）：クラスが所有する変数
    ・操作（メソッド）  ：クラスが所有する関数
    ・集約             ：他クラスを集約することができる

### メソッドの定義
    メソッドはまず関数ポインタを宣言し、そのポインタ変数をクラスに格納することで実現する。
    自身が格納されるクラスのポインタをメソッドの第一引数に指定する。

### クラスとメソッド宣言の例
```c
// まずはクラス型をtypedef宣言する
typedef _sampleClass sampleClass_t;

// メソッドを宣言する
typedef void (*method)(sampleClass_t *this, int a);

// クラスを定義する
struct _sampleClass {
    // 属性
    int field;
    // 操作
    method pMethod;
    // 集約
    anotherClass_t anotherClass;
};
```

### クラスの初期化
    以下の様に、まずはメソッドの実体を宣言＆定義する。
    次にクラスの初期値を変数として定義し、属性と操作をコンストラクタ関数で初期化する。
```c
// メソッドの実体を宣言
static void method (sampleClass_t *this, int a);

// クラスの初期値を定義
const sampleClass_t sampleClassInitValue = {
    0,
    &method
};

// メソッドの実体を定義
static void method (sampleClass_t *this, int a)
{
    printf ("field = %d\n", this->field);
}

// コンストラクタで初期化
void sampleClass_Constructor (sampleClass_t *this)
{
    this->field = sampleClassInitValue.field;
    this->pMethod = sampleClassInitValue.pMethod;
}
```
### インスタンスの生成と初期化
    以下のようにインスタンスを生成し、コンストラクタを呼び出して初期化する。
```c
sampleClass_t sampleClass;                  // 生成
sampleClass_Constructor (&sampleClass);     // 初期化
```

### メソッドの呼び出し
    別クラスなどから、以下のようにして呼び出す。
    第一引数には自身のクラスのポインタを渡す。
```c
sampleClass->method (&sampleClass, 1);
```
<br>

## ファイル構成
### ファイルの種類
    クラスは、2つのヘッダファイルと1つのcソースファイルから構成される。
    ・sampleClass.h ：クラス構造体の定義と、コンストラクタ関数の宣言を記述する。
    ・sample.h      ：クラス構造体とメソッドの関数ポインタの宣言を記述する。
                    　その他、列挙型や#define等も記述する。
    ・sample.c      ：クラスの本体を記述する。

### インクルード
    以下の順序でヘッダファイルをインクルードする。
    ① ：sampleClass.hはsample.hをインクルードする。
    ② ：sample.cはsampleClass.hをインクルードする。
    ③ ：別クラスを集約する場合は、sampleClass.hにanotherClass.hをインクルードする。
    ④ ：列挙型やメソッドのみ別クラスで参照したい場合は、sample.hをインクルードする。
![インクルード](include.jpg)
<br>


## 多態性
### 多態性
    クラス操作(関数ポインタ)に任意の関数を渡すことで、オブジェクト指向の多態性っぽいものを実現できる。

### 実現方法
    1. まず、メソッドとクラスメンバの初期値(sampleClassInitValue)を2つ以上宣言する。
    2. sampleClassInitValueをヘッダファイルにextern宣言する。
    3. コンストラクタの引数でsampleClassInitValueを受け取るように変更する。
    4. インスタンスの初期化時にsampleClassInitValueをコンストラクタに渡してやる。

```c : sample.c
/* sample.c */
// メソッドを2つ定義する
static void method1 (sampleClass_t *this, int a)
{
    printf ("value = %d\n", (this->field + a));
}

static void method2 (sampleClass_t *this, int a)
{
    printf ("value = %d\n", (this->field * a));
}

// クラスの初期値を2つ定義する
// それぞれ異なるフィールドとメソッドを初期値に指定しておく
const sampleClass_t sampleClassInitValue1 = {
    1,
    &method1
};

const sampleClass_t sampleClassInitValue2 = {
    2,
    &method2
};

// 初期値を引数で受け取るように変更する
void sampleClass_Constructor (sampleClass_t *this, sampleClass_t initValue)
{
    this->field = initValue.field;
    this->pMethod = initValue.pMethod;
}
```

```c : sampleClass.h
/* sampleClass.h */
// 初期値をextern宣言する
extern const sampleClass_t sampleClassInitValue1;
extern const sampleClass_t sampleClassInitValue2;
```

```c : another.c
/* another.c */
// インスタンスの初期化時に異なる初期値を与える
sampleClass_t instance1, instance2;
sampleClass_Constructor (&instance1, sampleClassInitValue1);
sampleClass_Constructor (&instance2, sampleClassInitValue2);

// メソッドを実行する
instance1->pMethod (&instance1, 2);
instance2->pMethod (&instance2, 2);
```
実行結果
```shell
value = 3
value = 4
```