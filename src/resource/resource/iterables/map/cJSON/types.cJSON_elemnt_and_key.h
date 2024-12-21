
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../imports/imports.macros.h"
//silver_chain_scope_end
#include "../unique.types_requrements.h"

#ifndef PRIVATE_DTW_CJSON_ELEMENT_AND_KEY_TYPE
#define PRIVATE_DTW_CJSON_ELEMENT_AND_KEY_TYPE
typedef  struct{
    char *key;
    bool free_key;
    cJSON *element;
}privateDtw_cJSON_element_and_key;

#endif
