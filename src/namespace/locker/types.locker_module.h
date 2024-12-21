
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end

#ifndef PRIVATE_DTW_LOCKER_MODULE_TYPE_H
#define PRIVATE_DTW_LOCKER_MODULE_TYPE_H
typedef struct DtwLockerModule{
    DtwLocker * (*newLocker)();
    int (*lock)(DtwLocker *self, const  char *element);
    void (*unlock)(DtwLocker *self, const  char *element);
    void (*represemt)(DtwLocker *self);
    void (*free)(DtwLocker *self);

}DtwLockerModule;

#endif
