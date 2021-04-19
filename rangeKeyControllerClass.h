#ifndef RANGE_KEY_CONTROLLER_CLASS_H
#define RANGE_KEY_CONTROLLER_CLASS_H

#include "rangeKeyController.h"

struct _rangeKeyController {
    char keyCode;
    char keyCodeBuff;
    int counter;

    funcScanKey pScanKey;
    funcGetKey pGetKey;
};

void rangeKeyController_Constructor (rangeKeyController_t *this);

#endif // RANGE_KEY_CONTROLLER_CLASS_H