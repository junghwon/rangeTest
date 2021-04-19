#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "rangeControllerClass.h"

static void startUp (rangeController_t *this);
static void wattSetting (rangeController_t *this);
static void timerSetting (rangeController_t *this);
static void start (rangeController_t *this);
static void stop (rangeController_t *this);
static void manager (rangeController_t *this);

const rangeController_t rangeControllerInitValue = {
    watt_500,
    0,
    &startUp,
    &wattSetting,
    &timerSetting,
    &start,
    &stop,
    &manager,
};

static void startUp (rangeController_t *this)
{
    this->rangeView.pStartUpDisplay (&this->rangeView);
}

static void wattSetting (rangeController_t *this)
{
    if (this->rangeKeyController.pGetKey (&this->rangeKeyController, 'w')) {
        switch (this->watt) {
            default:
            case watt_100:
                this->watt = watt_200;
            break;
            case watt_200:
                this->watt = watt_300;
            break;
            case watt_300:
                this->watt = watt_400;
            break;
            case watt_400:
                this->watt = watt_500;
            break;
            case watt_500:
                this->watt = watt_100;
            break;
        }
        this->rangeView.pWattDisplay (&this->rangeView, this->watt);
    }
}

static void timerSetting (rangeController_t *this)
{
    if (this->rangeKeyController.pGetKey (&this->rangeKeyController, 't')) {
        if (this->timer < TIMER_MAX) {
            this->timer += 10;
        } else {
            this->timer = 0;
        }
        this->rangeView.pTimerDisplay (&this->rangeView, this->timer);
    }
}

static void start (rangeController_t *this)
{
    if (this->rangeKeyController.pGetKey (&this->rangeKeyController, 's')) {
        this->rangeCookModel.pCookStart (&this->rangeCookModel, this->watt, this->timer);
        this->rangeView.pStartDisplay (&this->rangeView, this->watt, this->timer);
    }
}

static void stop (rangeController_t *this)
{
    this->watt = rangeControllerInitValue.watt;
    this->timer = rangeControllerInitValue.timer;
    this->rangeView.pStopDisplay (&this->rangeView);
}

static void manager (rangeController_t *this)
{
    state_t state = state_standby;

    state = this->rangeCookModel.pCookManager (
                &this->rangeCookModel,
                this->watt,
                this->timer,
                this->pStop,
                this);

    if (state == state_cook) {
        int timer = this->rangeCookModel.pGetCookTimer (&this->rangeCookModel);
        this->rangeView.pCookTimerDisplay (&this->rangeView, timer);
    }
}

void rangeController_Constructor (rangeController_t *this)
{
    this->watt = rangeControllerInitValue.watt;
    this->timer = rangeControllerInitValue.timer;

    this->pStartUp = rangeControllerInitValue.pStartUp;
    this->pWattSetting = rangeControllerInitValue.pWattSetting;
    this->pTimerSetting = rangeControllerInitValue.pTimerSetting;
    this->pStart = rangeControllerInitValue.pStart;
    this->pStop = rangeControllerInitValue.pStop;
    this->pRangeManager = rangeControllerInitValue.pRangeManager;

    rangeKeyController_Constructor (&this->rangeKeyController);
    rangeView_Constructor (&this->rangeView);
    rangeCookModel_Constructor (&this->rangeCookModel);
}