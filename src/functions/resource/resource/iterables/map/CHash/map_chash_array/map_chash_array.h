#define DTW_ALLOW_CHASH
#include "../unique.declaration_requirements.h"

CHashArray *DtwResource_map_CHashArray(
DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
CHash *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd
);

void  *private_dtw_CHashArray_callback(DtwResource *item,void *args);

bool private_dtw_CHashArray_filtrage(DtwResource *item,void *args);

int private_dtw_CHashArray_ordenation(DtwResource *item1,DtwResource *item2,void *args);

void privateDtwResource_add_to_item_to_CHashArray_array(void* array, void *item);
