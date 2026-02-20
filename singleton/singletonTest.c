#include <stdio.h>
#include "singletonTest.h"

/* シングルトンが共有する実データ */
static int sharedValue;

/* 内部的な唯一のインスタンス。value は sharedValue へのポインタ */
static singletonTest_t singletonTest = {
    .value = &sharedValue,
    .funcInit = NULL,
    .funcManager = NULL
};

static void init (void);
static void manager (int value);


static void init (void)
{
    *singletonTest.value = 0;
}

static void manager (int value)
{
    *singletonTest.value = value;
}

void singletonTest_Constructor (singletonTest_t *instance)
{
    /* 初回のみ初期化：funcInit が NULL なら未設定 */
    if (singletonTest.funcInit == NULL) {
        init ();
        singletonTest.funcInit = init;
        singletonTest.funcManager = manager;
    }

    if (instance != NULL) {
        *instance = singletonTest;
    }
}