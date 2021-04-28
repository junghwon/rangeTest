#ifndef SAMPLE_CLASS_H
#define SAMPLE_CLASS_H

/* include */
// sample.hをインクルードする
#include "sample.h"
// 集約したいクラスのヘッダをインクルードする
#include "anotherClass.h"
#include "interfaceSampleClass.h"


/* クラス定義 */
// sample.hで宣言したクラスの中身を定義する
struct _sample {
    // 属性
    data_t data;
    int value;
    // 操作
    funcManager pManager;
    funcSetting pSetting;
    // 集約
    another_t another;
    // インターフェース
    interfaceSample_t interface;
};

/* コンストラクタ宣言 */
void sample_Constructor (sample_t *this);

#endif // SAMPLE_CLASS_H