
void  *private_dtw_cJSON_callback(DtwResource *item,void *args) {
    private_DtwResource_cJSON_args *formmate_args = (private_DtwResource_cJSON_args*)args;
    return formmate_args->callback(item,formmate_args->args);
}

void privateDtwResource_add_to_item_to_array(void* array, void *item){
    cJSON_AddItemToArray((cJSON *)array, (cJSON *)item);
}

cJSON *DtwResource_map_cJSON(DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
cJSON *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd){

    cJSON *itens = cJSON_CreateArray();
    private_DtwResource_cJSON_args formated_args = {0};
    formated_args.callback = callback;
    formated_args.args = args;

    DtwResource_map(self,
        itens,
        privateDtwResource_add_to_item_to_array,
        filtrage_callback,
        private_dtw_cJSON_callback,
        &formated_args,
        start,
        qtd
        );

    return itens;
}




