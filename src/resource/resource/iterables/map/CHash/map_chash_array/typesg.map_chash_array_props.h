//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../../../../imports/imports.typesf.h"
//silver_chain_scope_end

#ifdef DTW_ALLOW_CHASH

typedef  struct{
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    CHash *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
} DtwResourceCHashrrayMapProps;
#endif
