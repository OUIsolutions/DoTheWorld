#include "../unique.types_requrements.h"
#include "../../Resource.h"

#ifndef PRIVATE_DTW_RESOURCE_CHASH_OBJECT_ARGS_TYPE_H
#define PRIVATE_DTW_RESOURCE_CHASH_OBJECT_ARGS_TYPE_H
typedef struct  {
    CHash *(*callback)(DtwResource *item,void *args);
    char *(*key_provider)(DtwResource *item,void *args);
    bool (*filtrage)(DtwResource *item,void *args);
    int (*ordenation)(DtwResource *item1,DtwResource *item2,void *args);
    void *args;
}private_DtwResource_CHashObject_args;
#endif
