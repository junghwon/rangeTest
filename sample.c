/* include */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
// sampleClass.hをインクルードする
#include "sampleClass.h"

/* メソッド宣言 */
// メソッドの関数を宣言する
// staticでファイル内関数として宣言する
static void manager (sample_t *this);
static void setting (sample_t *this);

/* クラス初期値 */
// クラスの初期値を定義する
// constで定数として定義する
const sample_t sampleInitValue = {
    // 属性
    data_0,
    0,
    // 操作
    &manager,
    &setting,
};

/* メソッド定義 */
// メソッドの関数を定義する
static void manager (sample_t *this)
{

}

static void setting (sample_t *this)
{

}

/* コンストラクタ定義 */
// クラスの各メンバを初期値で初期化する
void sample_Constructor (sample_t *this)
{
    // 属性
    this->data = sampleInitValue.data;
    this->value = sampleInitValue.value;

    // 操作
    this->pManager = sampleInitValue.pManager;
    this->pSetting = sampleInitValue.pSetting;

    // 集約
    // 集約したクラスのコンストラクタを実行する
    another_Constructor (&this->another);
}