
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../../imports/imports.macros.h"
//silver_chain_scope_end


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
