#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "rangeRelayModelClass.h"

static void relayOn (rangeRelayModel_t *this);
static void relayOff (rangeRelayModel_t *this);

const rangeRelayModel_t rangeRelayModelInitValue = {
    relayState_off,
    &relayOn,
    &relayOff,
};

static void relayOn (rangeRelayModel_t *this)
{
    this->relayState = relayState_on;
}

static void relayOff (rangeRelayModel_t *this)
{
    this->relayState = relayState_off;
}

void rangeRelayModel_Constructor (rangeRelayModel_t *this)
{
    this->relayState = rangeRelayModelInitValue.relayState;
    
    this->pRelayOn = rangeRelayModelInitValue.pRelayOn;
    this->pRelayOff = rangeRelayModelInitValue.pRelayOff;
}