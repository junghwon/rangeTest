#ifndef RANGE_MAGNETRON_MODEL_H
#define RANGE_MAGNETRON_MODEL_H

#include "rangeController.h"

typedef enum {
    mqOnTime_100w = 1,
    mqOnTime_200w = 3,
    mqOnTime_300w = 5,
    mqOnTime_400w = 7,
    mqOnTime_500w = 9,
} mqOnTime_t;

typedef enum {
    mqOffTime_100w = 9,
    mqOffTime_200w = 7,
    mqOffTime_300w = 5,
    mqOffTime_400w = 3,
    mqOffTime_500w = 1,
} mqOffTime_t;

typedef enum {
    mqState_off,
    mqState_on,
} mqState_t;

typedef struct _rangeMagnetronModel rangeMagnetronModel_t;

typedef void (*funcManager)(rangeMagnetronModel_t *this);
typedef void (*funcInit)(rangeMagnetronModel_t *this);
typedef void (*funcMqStart)(rangeMagnetronModel_t *this,  watt_t watt);

#endif // RANGE_MAGNETRON_MODEL_H