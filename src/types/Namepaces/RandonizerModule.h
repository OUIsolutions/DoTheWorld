
#include "unique.all_types_less_dependencies.h"

#ifndef PRIVATE_DTW_RANDONIZER_MODULE_TYPE_H
#define PRIVATE_DTW_RANDONIZER_MODULE_TYPE_H
typedef struct  DtwRandonizerModule{
    DtwRandonizer * (*newRandonizer)();
    int (*generate_num)(DtwRandonizer *self,int max);
    char * (*generate_token)(DtwRandonizer*self, int size);
    void (*free)(DtwRandonizer *self);
}DtwRandonizerModule;
#endif
