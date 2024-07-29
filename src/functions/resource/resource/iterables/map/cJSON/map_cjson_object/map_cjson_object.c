#include "../unique.definition_requirements.h"

void  *private_dtw_cJSONObject_callback(DtwResource *item,void *args) {
    private_DtwResource_cJSONObject_args *formmate_args = (private_DtwResource_cJSONObject_args*)args;
    privateDtw_cJSON_element_and_key *created = (privateDtw_cJSON_element_and_key*)malloc(sizeof(privateDtw_cJSON_element_and_key));
    created->key = formmate_args->key_provider(item,args);
    created->element =formmate_args->callback(item,formmate_args->args);
    return (void*)created;
}

bool private_dtw_cJSONObject_filtrage(DtwResource *item,void *args) {
    private_DtwResource_cJSONObject_args *formmate_args = (private_DtwResource_cJSONObject_args*)args;
    return formmate_args->filtrage(item,formmate_args->args);
}

int private_dtw_cJSONObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) {
    private_DtwResource_cJSONObject_args *formmate_args = (private_DtwResource_cJSONObject_args*)args;
    return formmate_args->ordenation(item1,item2,formmate_args->args);
}

void privateDtwResource_add_to_item_to_cJSONObject(void* object, void *item){
    privateDtw_cJSON_element_and_key *casted = (privateDtw_cJSON_element_and_key*)item;
    cJSON_AddItemToObject((cJSON*)object,casted->key,casted->element);
    free(casted->key);
    free(casted);
}


cJSON *DtwResource_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props){

    cJSON *itens = cJSON_CreateObject();

    private_DtwResource_cJSONObject_args formated_args = {0};
    formated_args.callback = props.callback;
    formated_args.filtrage = props.filtrage_callback;
    formated_args.key_provider = props.key_provider_callback;
    formated_args.ordenation = props.ordenation_callback;
    formated_args.args = props.args;


    bool (*filtrage)(DtwResource *,void *) = NULL;
    if(props.filtrage_callback) {
        filtrage = private_dtw_cJSONObject_filtrage;
    }
    int (*ordenation)(DtwResource *,DtwResource *,void *) = NULL;
    if(ordenation_callback) {
        ordenation = private_dtw_cJSONObject_ordenation;
    }

    DtwResource_map(self,
        itens,
        privateDtwResource_add_to_item_to_cJSONObject,
        filtrage,
        ordenation,
        private_dtw_cJSONObject_callback,
        &formated_args,
        start,
        qtd
        );

    return itens;
}
