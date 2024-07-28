#include "../unique.definition_requirements.h"


void privateDtwResource_add_to_item_to_cJSONArray_array(void* array, void *item){
    cJSON_AddItemToArray((cJSON *)array, (cJSON *)item);
}

cJSON *DtwResource_map_cJSONArray(DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
cJSON *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd){

    cJSON *itens = cJSON_CreateArray();

    DtwResource_map(self,
        itens,
        privateDtwResource_add_to_item_to_cJSONArray_array,
        filtrage_callback,
        ordenation_callback,
       (void *(*)(DtwResource *, void *))callback,
        args,
        start,
        qtd
        );

    return itens;
}
