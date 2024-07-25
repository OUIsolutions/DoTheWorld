

#include "../unique.h"

cJSON *DtwResource_map_cJSON(
DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
cJSON *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd
);

void  *private_dtw_cJSON_callback(DtwResource *item,void *args);

bool private_dtw_cJSON_filtrage(DtwResource *item,void *args);

int private_dtw_cJSON_ordenation(DtwResource *item1,DtwResource *item2,void *args);

void privateDtwResource_add_to_item_to_array(void* array, void *item);
