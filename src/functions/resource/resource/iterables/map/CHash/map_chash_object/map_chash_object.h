
#define DTW_ALLOW_CHASH
#include "../unique.declaration_requirements.h"


CHash *DtwResource_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);

CHash *DtwResource_schema_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);

void  *private_dtw_CHashArray_callback(DtwResource *item,void *args);

bool private_dtw_CHashArray_filtrage(DtwResource *item,void *args);

int private_dtw_CHashArray_ordenation(DtwResource *item1,DtwResource *item2,void *args);

void privateDtwResource_add_to_item_to_CHashObject(void* object, void *item);
