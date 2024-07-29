#include "../unique.types_requrements.h"
#include "../../../Resource.h"

#ifndef PRIVATE_DTW_RESOURCE_CJSON_OBJECT_ARGS_TYPE_H
#define PRIVATE_DTW_RESOURCE_CJSON_OBJECT_ARGS_TYPE_H
typedef struct  {
    cJSON *(*callback)(DtwResource *item,void *args);
    char *(*key_provider)(DtwResource *item,void *args);
    bool (*filtrage)(DtwResource *item,void *args);
    int (*ordenation)(DtwResource *item1,DtwResource *item2,void *args);
    void *args;
}private_DtwResource_cJSONObject_args;
#endif
