
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../../../imports/imports.globals.h"
//silver_chain_scope_end
#ifdef DTW_ALLOW_CHASH


DtwResourceCHashrrayMapProps  DtwResource_create_CHashrrayMapProps(    CHash *(*callback)(DtwResource *item, void *args));

CHashArray *DtwResource_map_CHashArray(DtwResource *self,DtwResourceCHashrrayMapProps props);

CHashArray *DtwResource_schema_map_CHashArray(DtwResource *self,DtwResourceCHashrrayMapProps props);

void  *private_dtw_CHashArray_callback(DtwResource *item,void *args);

bool private_dtw_CHashArray_filtrage(DtwResource *item,void *args);

int private_dtw_CHashArray_ordenation(DtwResource *item1,DtwResource *item2,void *args);

void privateDtwResource_add_to_item_to_CHashArray_array(void* array, void *item);
#endif
