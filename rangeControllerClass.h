#ifndef RANGE_CONTROLLER_CLASS_H
#define RANGE_CONTROLLER_CLASS_H

#include "rangeController.h"
#include "rangeKeyControllerClass.h"
#include "rangeViewClass.h"
#include "rangeCookModelClass.h"

struct _rangeController {
    watt_t watt;
    int timer;

    funcStartUp pStartUp;
    funcWattSetting pWattSetting;
    funcTimerSetting pTimerSetting;
    funcStart pStart;
    funcStop pStop;
    funcRangeManager pRangeManager;

    rangeKeyController_t rangeKeyController;
    rangeView_t rangeView;
    rangeCookModel_t rangeCookModel;
};

void rangeController_Constructor (rangeController_t *this);

#endif // RANGE_CONTROLLER_CLASS_H