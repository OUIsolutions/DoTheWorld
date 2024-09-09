#include "../unique.types_requrements.h"
#include "../../../Resource.h"

#ifndef PRIVATE_DTW_RESOURCE_CJSON_ARRAY_MAP_PROPS
#define PRIVATE_DTW_RESOURCE_CJSON_ARRAY_MAP_PROPS
typedef  struct{
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    cJSON *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
} DtwResourcecJSONArrayMapProps;
#endif
