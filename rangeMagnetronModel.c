#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "rangeMagnetronModelClass.h"

static void manager (rangeMagnetronModel_t *this);
static void init (rangeMagnetronModel_t *this);
static void mqStart (rangeMagnetronModel_t *this, watt_t watt);

const rangeMagnetronModel_t rangeMagnetronModelInitValue = {
    mqOnTime_500w,
    mqOffTime_500w,
    mqState_off,
    0,
    &manager,
    &init,
    &mqStart,
};

static void mqOn (rangeMagnetronModel_t *this)
{
    this->rangeRelayModel.pRelayOn (&this->rangeRelayModel);

    if (this->mqCounter <= 0) {
        printf ("MQ OFF\n");
        this->state = mqState_off;
        this->mqCounter = (int)this->mqOffTime;
        this->rangeTimerModel.pSetTimer (&this->rangeTimerModel, &this->mqCounter);
    }
}

static void mqOff (rangeMagnetronModel_t *this)
{
    this->rangeRelayModel.pRelayOff (&this->rangeRelayModel);

    if (this->mqCounter <= 0) {
        printf ("MQ ON\n");
        this->state = mqState_on;
        this->mqCounter = (int)this->mqOnTime;
        this->rangeTimerModel.pSetTimer (&this->rangeTimerModel, &this->mqCounter);
    }
}

static void manager (rangeMagnetronModel_t *this)
{
    switch (this->state) {
        default:
        case mqState_off:
            mqOff (this);
        break;
        case mqState_on:
            mqOn (this);
        break;
    }
}

static void init (rangeMagnetronModel_t *this)
{
    this->state = rangeMagnetronModelInitValue.state;
    this->mqOffTime = rangeMagnetronModelInitValue.mqOffTime;
    this->mqOnTime = rangeMagnetronModelInitValue.mqOnTime;
    this->mqCounter = rangeMagnetronModelInitValue.mqCounter;
    this->rangeTimerModel.pInitTimer (&this->rangeTimerModel);
    this->rangeRelayModel.pRelayOff (&this->rangeRelayModel);
}

static void mqStart (rangeMagnetronModel_t *this, watt_t watt)
{
    switch (watt) {
        default:
        case watt_100:
            this->mqOnTime = mqOnTime_100w;
            this->mqOffTime = mqOffTime_100w;
        break;
        case watt_200:
            this->mqOnTime = mqOnTime_200w;
            this->mqOffTime = mqOffTime_200w;
        break;
        case watt_300:
            this->mqOnTime = mqOnTime_300w;
            this->mqOffTime = mqOffTime_300w;
        break;
        case watt_400:
            this->mqOnTime = mqOnTime_400w;
            this->mqOffTime = mqOffTime_400w;
        break;
        case watt_500:
            this->mqOnTime = mqOnTime_500w;
            this->mqOffTime = mqOffTime_500w;
        break;
    }

    this->state = mqState_on;
    this->mqCounter = (int)this->mqOnTime;
    this->rangeTimerModel.pSetTimer (&this->rangeTimerModel, &this->mqCounter);
}

void rangeMagnetronModel_Constructor (rangeMagnetronModel_t *this)
{
    this->mqOnTime = rangeMagnetronModelInitValue.mqOnTime;
    this->mqOnTime = rangeMagnetronModelInitValue.mqOffTime;
    this->state = rangeMagnetronModelInitValue.state;
    this->mqCounter = rangeMagnetronModelInitValue.mqCounter;

    this->manager = rangeMagnetronModelInitValue.manager;
    this->init = rangeMagnetronModelInitValue.init;
    this->mqStart = rangeMagnetronModelInitValue.mqStart;

    rangeTimerModel_Constructor (&this->rangeTimerModel);
    rangeRelayModel_Constructor (&this->rangeRelayModel);
}