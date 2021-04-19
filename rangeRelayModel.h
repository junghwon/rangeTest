#ifndef RANGE_RELAY_MODEL_H
#define RANGE_RELAY_MODEL_H

typedef enum {
    relayState_off,
    relayState_on,
} raleyState_t;

typedef struct _rangeRelayModel rangeRelayModel_t;

typedef void (*funcRelayOn)(rangeRelayModel_t *this);
typedef void (*funcRelayOff)(rangeRelayModel_t *this);

#endif // RANGE_RELAY_MODEL_H