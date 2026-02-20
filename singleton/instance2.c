#include <stdio.h>
#include "singletonTest.h"
#include "instance2.h"

static singletonTest_t singletonInstance2;

void instance2 (void)
{
    singletonTest_Constructor (&singletonInstance2);

    printf ("instance2_value = %d\n", *singletonInstance2.value);
}