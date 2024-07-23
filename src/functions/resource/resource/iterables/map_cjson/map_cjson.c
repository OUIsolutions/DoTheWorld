


cJSON *DtwResource_map_cJSON(DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
cJSON *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd){

    cJSON *itens = cJSON_CreateArray();

    DtwResource_map(self, itens, privateDtwResource_add_to_item_to_array, filtrage_callback, callback, args, start, qtd);

    return itens;
}


void privateDtwResource_add_to_item_to_array(void* array, void *item){


    cJSON_AddItemToArray((cJSON *)array, (cJSON *)item);
}


