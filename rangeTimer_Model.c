#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "rangeTimerModelClass.h"

static void setTimer (rangeTimerModel_t *this, int *timer);
static void initTimer (rangeTimerModel_t *this);
static void countTimer (rangeTimerModel_t *this);

const rangeTimerModel_t rangeTimerModelInitValue = {
    0,
    false,
    &setTimer,
    &initTimer,
    &countTimer,
};

static void setTimer (rangeTimerModel_t *this, int *timer)
{
    this->timer = timer;
    this->countEnable = true;
}

static void initTimer (rangeTimerModel_t *this)
{
    this->timer = rangeTimerModelInitValue.timer;
    this->countEnable = false;
}

static void countTimer (rangeTimerModel_t *this)
{
    if (this->countEnable == true) {
        if (this->timer) {
            (*this->timer)--;
        }
    }
    sleep (1);
}

void rangeTimerModel_Constructor (rangeTimerModel_t *this)
{
    this->timer = rangeTimerModelInitValue.timer;
    this->countEnable = rangeTimerModelInitValue.countEnable;
    
    this->pSetTimer = rangeTimerModelInitValue.pSetTimer;
    this->pInitTimer = rangeTimerModelInitValue.pInitTimer;
    this->pCountTimer = rangeTimerModelInitValue.pCountTimer;
}