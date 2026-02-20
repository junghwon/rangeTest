#ifndef SINGLETON_TEST_H
#define SINGLETON_TEST_H

typedef struct _singletonTest singletonTest_t;
typedef void (*funcInit)(void);
typedef void (*funcManager)(int value);

/*
 * シングルトンとして共通のデータ領域を持たせるため、
 * グローバルな static インスタンスを constructor でコピーする。
 */
struct _singletonTest {
    /* 実際の整数はシングルトン内の単一変数を指すポインタ
       (複製されたインスタンスでも同じメモリを共有) */
    int *value;

    funcInit funcInit;
    funcManager funcManager;
};

void singletonTest_Constructor (singletonTest_t *instance);

#endif // SINGLETON_TEST_H