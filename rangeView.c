#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "rangeViewClass.h"
#include "rangeControllerClass.h"

static void startUpDisplay (rangeView_t *this);
static void wattDisplay (rangeView_t *this, watt_t watt);
static void timerDisplay (rangeView_t *this, int timer);
static void startDisplay (rangeView_t *this, watt_t watt, int timer);
static void stopDisplay (rangeView_t *this);
static void cookTimerDisplay (rangeView_t *this, int timer);

const rangeView_t rangeViewInitValue = {
    &startUpDisplay,
    &wattDisplay,
    &timerDisplay,
    &startDisplay,
    &stopDisplay,
    &cookTimerDisplay,
};

static int creatDisplayWatt (watt_t watt)
{
    int rsp = 0;
    switch (watt) {
        default:
        case watt_100:
            rsp = 100;
        break;
        case watt_200:
            rsp = 200;
        break;
        case watt_300:
            rsp = 300;
        break;
        case watt_400:
            rsp = 400;
        break;
        case watt_500:
            rsp = 500;
        break;
    }

    return (rsp);
}

static void startUpDisplay (rangeView_t *this)
{
    printf ("Range starting up now...\n");
}

static void wattDisplay (rangeView_t *this, watt_t watt)
{
    printf ("Watt : %dw\n", creatDisplayWatt (watt));
}

static void timerDisplay (rangeView_t *this, int timer)
{
    printf ("Cook timer : %dsec\n", timer);
}

static void startDisplay (rangeView_t *this, watt_t watt, int timer)
{
    printf ("Cook start : Watt=%dw, Timer=%dsec\n", creatDisplayWatt (watt), timer);
}

static void stopDisplay (rangeView_t *this)
{
    printf ("Cook stop\n");
}

static void cookTimerDisplay (rangeView_t *this, int timer)
{
    static int buff = 0;

    if (timer != buff) {
        buff = timer;
        printf ("Remain time : %dsec\n", timer);
    }    
}

void rangeView_Constructor (rangeView_t *this)
{
    this->pStartUpDisplay = rangeViewInitValue.pStartUpDisplay;
    this->pWattDisplay = rangeViewInitValue.pWattDisplay;
    this->pTimerDisplay = rangeViewInitValue.pTimerDisplay;
    this->pStartDisplay = rangeViewInitValue.pStartDisplay;
    this->pStopDisplay = rangeViewInitValue.pStopDisplay;
    this->pCookTimerDisplay = rangeViewInitValue.pCookTimerDisplay;
}