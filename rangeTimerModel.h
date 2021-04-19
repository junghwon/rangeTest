#ifndef RANGEE_TIMER_MODEL_H
#define RANGEE_TIMER_MODEL_H

typedef struct _rangeTimeModel rangeTimerModel_t;

typedef void (*funcSetTimer)(rangeTimerModel_t *this, int *time);
typedef void (*funcInitTimer)(rangeTimerModel_t *this);
typedef void (*funcCountTimer)(rangeTimerModel_t *this);

#endif // RANGEE_TIMER_MODEL_H