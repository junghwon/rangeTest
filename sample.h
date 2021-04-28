#ifndef SAMPLE_H
#define SAMPLE_H

/* データ定義 */
// 外部に公開したいデータ（defineやenum）はここに記載する
#define SAMPLE_DEFINE (0)

typedef enum {
    data_0,
    data_1,
} data_t;

/* クラス宣言 */
// クラスの名前をtypedef宣言しておく
typedef struct _sample sample_t;

/* メソッド宣言 */
// メソッドの関数ポインタをtypedef宣言する
// 第一引数にはクラスのポインタを指定する
typedef void (*funcManager)(sample_t *this);
typedef void (*funcSetting)(sample_t *this);

#endif // SAMPLE_H