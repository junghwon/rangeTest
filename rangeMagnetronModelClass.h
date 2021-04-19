#ifndef RANGE_MAGNETRON_MODEL_CLASS_H
#define RANGE_MAGNETRON_MODEL_CLASS_H

#include "rangeMagnetronModel.h"
#include "rangeTimerModelClass.h"
#include "rangeRelayModelClass.h"

struct _rangeMagnetronModel {
    mqOnTime_t mqOnTime;
    mqOffTime_t mqOffTime;
    mqState_t state;
    int mqCounter;

    funcManager manager;
    funcInit init;
    funcMqStart mqStart;

    rangeTimerModel_t rangeTimerModel;
    rangeRelayModel_t rangeRelayModel;
};

void rangeMagnetronModel_Constructor (rangeMagnetronModel_t *this);

#endif // RANGE_MAGNETRON_MODEL_CLASS_H