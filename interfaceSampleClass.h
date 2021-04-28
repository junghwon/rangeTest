#ifndef INTERFACE_CLASS_SAMPLE_H
#define INTERFACE_CLASS_SAMPLE_H

#include "interfaceSample.h"

struct _interfaceSample {
    funcManager pManager;
};

extern const interfaceSample_t interfaceSampleInitValue;
void interfaceSample_Constructor (interfaceSample_t *this, interfaceSample_t initValue);

#endif // INTERFACE_CLASS_SAMPLE_H