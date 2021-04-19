#ifndef RANGE_COOK_MODEL_CLASS_H
#define RANGE_COOK_MODEL_CLASS_H

#include "rangeCookModel.h"
#include "rangeTimerModelClass.h"
#include "rangeMagnetronModelClass.h"

struct _rangeCookModel {
    state_t state;
    int cookTimer;

    funcCookManager pCookManager;
    funcCookStart pCookStart;
    funcGetCookTimer pGetCookTimer;

    rangeTimerModel_t rangeTimerModel;
    rangeMagnetronModel_t rangeMagnetronModel;
};

void rangeCookModel_Constructor (rangeCookModel_t *this);

#endif // RANGE_COOK_MODEL_CLASS_H