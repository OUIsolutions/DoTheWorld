
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../imports/imports.types.h"
//silver_chain_scope_end

#ifndef  PRIVATE_DTW_FLOCK_ARRAY_TYPE_H
#define PRIVATE_DTW_FLOCK_ARRAY_TYPE_H

typedef struct {
    privateDtwFlockLockedElement **elements;
    int size;
}privateDtwFlockArray;
#endif
