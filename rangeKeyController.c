#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "rangeKeyControllerClass.h"

static void scanKey (rangeKeyController_t *this);
static int getKey (rangeKeyController_t *this, int key);

const rangeKeyController_t rangeKeyControllerInitValue = {
    ' ',
    ' ',
    0,
    &scanKey,
    &getKey,
};

static void scanKey (rangeKeyController_t *this)
{
    this->keyCodeBuff = getchar();
    if (this->keyCodeBuff != '\n') {
        this->counter = true;
        this->keyCode = this->keyCodeBuff;
    }
}

static int getKey (rangeKeyController_t *this, int key)
{
    int rsp = false;

    if (this->counter == true) {
        if (this->keyCode == (char)key) {
            this->counter = false;
            rsp = true;
        }
    }

    return (rsp);
}

void rangeKeyController_Constructor (rangeKeyController_t *this)
{
    this->keyCodeBuff = rangeKeyControllerInitValue.keyCodeBuff;
    this->keyCode = rangeKeyControllerInitValue.keyCode;
    this->counter = rangeKeyControllerInitValue.counter;
    
    this->pScanKey = rangeKeyControllerInitValue.pScanKey;
    this->pGetKey = rangeKeyControllerInitValue.pGetKey;
}
