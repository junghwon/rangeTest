#ifndef RANGE_VIEW_CLASS_H
#define RANGE_VIEW_CLASS_H

#include "rangeView.h"

struct _rangeView {
    funcStartUpDisplay pStartUpDisplay;
    funcWattDisplay pWattDisplay;
    funcTimerDisplay pTimerDisplay;
    funcStartDisplay pStartDisplay;
    funcStopDisplay pStopDisplay;
    funcCookTimerDisplay pCookTimerDisplay;
};

void rangeView_Constructor (rangeView_t *this);

#endif // RANGE_VIEW_CLASS_H