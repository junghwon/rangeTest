#include <stdio.h>
#include "singletonTest.h"
#include "instance1.h"

static singletonTest_t singletonInstance;

void instance1 (void)
{
    singletonTest_Constructor (&singletonInstance);

    singletonInstance.funcManager (3);
    printf ("instance1_value = %d\n", *singletonInstance.value);
}