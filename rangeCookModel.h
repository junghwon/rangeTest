#ifndef RANGE_COOK_MODEL_H
#define RANGE_COOK_MODEL_H

#include "rangeController.h"

typedef enum {
    state_standby,
    state_cook,
    state_end,
} state_t;

typedef struct _rangeCookModel rangeCookModel_t;

typedef state_t (*funcCookManager)(
    rangeCookModel_t *this,
    watt_t watt,
    int timer,
    funcStop callback,
    rangeController_t *rangeController);
typedef void (*funcCookStart)(rangeCookModel_t *this, watt_t watt, int timer);
typedef int (*funcGetCookTimer)(rangeCookModel_t *this);

#endif // RANGE_COOK_MODEL_H