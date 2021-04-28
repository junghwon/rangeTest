#include "interfaceSampleClass.h"

void interfaceSample_Constructor (interfaceSample_t *this, interfaceSample_t initValue)
{
    this->pManager = initValue.pManager;
    this->pInit = initValue.pInit;
}

