#include "unique.all_types_less_dependencies.h"

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
