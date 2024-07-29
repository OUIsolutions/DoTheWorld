#include "../../Resource.h"


#ifndef PRIVATE_DTW_RESOURCE_CHASH_ARRAY_ARGS_TYPE_H
#define PRIVATE_DTW_RESOURCE_CHASH_ARRAY_ARGS_TYPE_H
typedef struct  {
    CHash *(*callback)(DtwResource *item,void *args);
    bool (*filtrage)(DtwResource *item,void *args);
    int (*ordenation)(DtwResource *item1,DtwResource *item2,void *args);
    void *args;
}private_DtwResource_CHashArray_args;
#endif
