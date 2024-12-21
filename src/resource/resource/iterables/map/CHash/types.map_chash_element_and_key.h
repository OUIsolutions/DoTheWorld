
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../imports/imports.macros.h"
//silver_chain_scope_end


#define DTW_ALLOW_CHASH

#ifndef PRIVATE_DTW_CHASH_ELEMENT_AND_KEY_TYPE
#define PRIVATE_DTW_CHASH_ELEMENT_AND_KEY_TYPE
typedef  struct{
    char *key;
    CHash *element;
    bool free_key;
}privateDtw_CHash_element_and_key;

#endif
