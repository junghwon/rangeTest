#ifndef RANGE_VIEW_H
#define RANGE_VIEW_H

#include "rangeController.h"

typedef struct _rangeView rangeView_t;

typedef void (*funcStartUpDisplay)(struct _rangeView *this);
typedef void (*funcWattDisplay)(struct _rangeView *this, watt_t watt);
typedef void (*funcTimerDisplay)(struct _rangeView *this, int timer); 
typedef void (*funcStartDisplay)(struct _rangeView *this, watt_t watt, int timer);
typedef void (*funcStopDisplay)(struct _rangeView *this);
typedef void (*funcCookTimerDisplay)(struct _rangeView *this, int timer); 

#endif // RANGE_VIEW_H