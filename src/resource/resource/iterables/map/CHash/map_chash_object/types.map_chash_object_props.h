
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../../imports/imports.macros.h"
//silver_chain_scope_end
#include "../unique.types_requrements.h"
#include "../../../Resource.h"

#ifndef PRIVATE_DTW_RESOURCE_CHASH_OBJECT_MAP_PROPS
#define PRIVATE_DTW_RESOURCE_CHASH_OBJECT_MAP_PROPS
typedef  struct{
    char *(*key_provider_callback)(DtwResource *item,void *args);
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    CHash *(*callback)(DtwResource *item, void *args);
    void *args;
    bool free_key;
    int start;
    int qtd;
} DtwResourceCHashObjectMapProps;
#endif
