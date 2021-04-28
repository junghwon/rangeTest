#include "interfaceSampleClass.h"

static void manager (interfaceSample_t *this);

const interfaceSample_t interfaceSampleInitValue = {
    &manager,
};

static void manager (interfaceSample_t *this)
{

}

void interfaceSample_Constructor (interfaceSample_t *this, interfaceSample_t initValue)
{
    this->pManager = initValue.pManager;
}

