#ifndef RANGE_KEY_CONTROLLER_H
#define RANGE_KEY_CONTROLLER_H

typedef struct _rangeKeyController rangeKeyController_t;

typedef void (*funcScanKey)(rangeKeyController_t *this);
typedef int (*funcGetKey)(rangeKeyController_t *this, int key);

#endif // RANGE_KEY_CONTROLLER_H