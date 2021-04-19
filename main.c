#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include "rangeControllerClass.h"

static void scanThread (rangeKeyController_t *instance);
static void mainThread (rangeController_t *instance);
static void timerThread (rangeTimerModel_t *instance);
static void mqTimerThread (rangeTimerModel_t *instance);

int main (int argc, char *argv[])
{
    rangeController_t rangeController;
    rangeController_Constructor (&rangeController);    

    pthread_t thread1, thread2, thread3, thread4;
    int ret1, ret2, ret3, ret4;

    ret1 = pthread_create (&thread1, NULL, (void *)scanThread, &rangeController.rangeKeyController);
    ret2 = pthread_create (&thread2, NULL, (void *)mainThread, &rangeController);
    ret3 = pthread_create (&thread3, NULL, (void *)timerThread, &rangeController.rangeCookModel.rangeTimerModel);
    ret4 = pthread_create (&thread4, NULL, (void *)mqTimerThread, &rangeController.rangeCookModel.rangeMagnetronModel.rangeTimerModel);

    ret1 = pthread_join (thread1, NULL);
    ret2 = pthread_join (thread2, NULL);
    ret3 = pthread_join (thread3, NULL);
    ret4 = pthread_join (thread4, NULL);

    return (0);
}

static void scanThread (rangeKeyController_t *instance)
{ 
    while (1) {
        instance->pScanKey (instance);
    }
}

static void mainThread (rangeController_t *instance)
{
    instance->pStartUp (instance);

    while (1) {
        instance->pWattSetting (instance);
        instance->pTimerSetting (instance);
        instance->pStart (instance);
        instance->pRangeManager (instance);
    }
}

static void timerThread (rangeTimerModel_t *instance)
{
    while (1) {
        instance->pCountTimer (instance);
    }
}

static void mqTimerThread (rangeTimerModel_t *instance)
{
    while (1) {
        instance->pCountTimer (instance);
    }
}