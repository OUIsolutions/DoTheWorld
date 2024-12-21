
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../imports/imports.macros.h"
//silver_chain_scope_end


#ifdef DTW_ALLOW_CHASH


typedef  struct{
    char *key;
    CHash *element;
    bool free_key;
}privateDtw_CHash_element_and_key;

#endif
