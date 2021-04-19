#ifndef RANGE_RELAY_MODEL_CLASS_H
#define RANGE_RELAY_MODEL_CLASS_H

#include "rangeRelayModel.h"

struct _rangeRelayModel {
    raleyState_t relayState;
    
    funcRelayOn pRelayOn;
    funcRelayOff pRelayOff;
};

void rangeRelayModel_Constructor (rangeRelayModel_t *this);

#endif // RANGE_RELAY_MODEL_CLASS_H