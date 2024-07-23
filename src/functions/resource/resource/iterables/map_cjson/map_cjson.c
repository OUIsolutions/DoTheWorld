
void  *private_dtw_cJSON_callback(DtwResource *item,void *args) {
    private_DtwResource_cJSON_args *formmate_args = (private_DtwResource_cJSON_args*)args;
    return (void*)formmate_args->callback(item,formmate_args->args);
}

bool private_dtw_cJSON_filtrage(DtwResource *item,void *args) {
    private_DtwResource_cJSON_args *formmate_args = (private_DtwResource_cJSON_args*)args;
    return formmate_args->filtrage(item,formmate_args->args);
}

int private_dtw_cJSON_ordenation(DtwResource *item1,DtwResource *item2,void *args) {
    private_DtwResource_cJSON_args *formmate_args = (private_DtwResource_cJSON_args*)args;
    return formmate_args->ordenation(item1,item2,formmate_args->args);
}

void privateDtwResource_add_to_item_to_array(void* array, void *item){
    cJSON_AddItemToArray((cJSON *)array, (cJSON *)item);
}

cJSON *DtwResource_map_cJSON(DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
cJSON *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd){

    cJSON *itens = cJSON_CreateArray();
    private_DtwResource_cJSON_args formated_args = {0};
    formated_args.callback = callback;
    formated_args.filtrage = filtrage_callback;
    formated_args.ordenation = ordenation_callback;
    formated_args.args = args;

    bool (*filtrage)(DtwResource *,void *) = NULL;
    if(filtrage_callback) {
        filtrage = private_dtw_cJSON_filtrage;
    }
    int (*ordenation)(DtwResource *,DtwResource *,void *) = NULL;
    if(ordenation_callback) {
        ordenation = private_dtw_cJSON_ordenation;
    }

    DtwResource_map(self,
        itens,
        privateDtwResource_add_to_item_to_array,
        filtrage,
        ordenation,
        private_dtw_cJSON_callback,
        &formated_args,
        start,
        qtd
        );

    return itens;
}




