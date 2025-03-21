//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../../../../imports/imports.typesm.h"
//silver_chain_scope_end


#ifdef DTW_ALLOW_CHASH


DtwResourceCHashObjectMapProps DtwResource_createCHashObjectMapProps(
    CHash *(*callback)(DtwResource *item, void *args),
    char *(*filtrage_callback)(DtwResource *item, void *args_filter)
);

CHash *DtwResource_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);

CHash *DtwResource_schema_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);

void  *private_dtw_CHashArray_callback(DtwResource *item,void *args);

bool private_dtw_CHashArray_filtrage(DtwResource *item,void *args);

int private_dtw_CHashArray_ordenation(DtwResource *item1,DtwResource *item2,void *args);

void privateDtwResource_add_to_item_to_CHashObject(void* object, void *item);
#endif
