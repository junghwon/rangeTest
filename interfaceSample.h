#ifndef INTERFACE_SAMPLE_H
#define INTERFACE_SAMPLE_H

typedef struct _interfaceSample interfaceSample_t;

extern const interfaceSample_t interfaceSampleInitValue;
typedef void (*funcManager)(interfaceSample_t *this);

#endif // INTERFACE_SAMPLE_H