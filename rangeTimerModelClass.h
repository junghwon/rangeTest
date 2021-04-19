#ifndef RANGE_TIMER_MODEL_CLASS_H
#define RANGE_TIMER_MODEL_CLASS_H

#include "rangeTimerModel.h"

struct _rangeTimeModel {
    int *timer;
    int countEnable;

    funcSetTimer pSetTimer;
    funcInitTimer pInitTimer;
    funcCountTimer pCountTimer;
};

void rangeTimerModel_Constructor (rangeTimerModel_t *this);

#endif // RANGE_TIMER_MODEL_CLASS_H