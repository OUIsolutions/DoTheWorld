#include "FlockLockedElement.h"

#ifndef  PRIVATE_DTW_FLOCK_ARRAY_TYPE_H
#define PRIVATE_DTW_FLOCK_ARRAY_TYPE_H

typedef struct {
    privateDtwFlockLockedElement **elements;
    int size;
}privateDtwFlockArray;
#endif
