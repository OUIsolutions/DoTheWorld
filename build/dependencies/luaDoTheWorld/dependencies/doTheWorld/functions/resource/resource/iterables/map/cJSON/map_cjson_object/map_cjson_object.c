#include "../unique.definition_requirements.h"

DtwResourcecJSONObjectMapProps DtwResource_create_cJSONObjectProps(
    cJSON *(*callback)(DtwResource *item, void *args),
    char *(*key_provider_callback)(DtwResource *item,void *args)
){
    DtwResourcecJSONObjectMapProps props = {0};
    props.callback  = callback;
    props.key_provider_callback = key_provider_callback;
    props.qtd = DTW_RESOURCE_ALL;
    return  props;
}

void  *private_dtw_cJSONObject_callback(DtwResource *item,void *args) {
    DtwResourcecJSONObjectMapProps *formmate_args = (DtwResourcecJSONObjectMapProps*)args;
    privateDtw_cJSON_element_and_key *created = (privateDtw_cJSON_element_and_key*)malloc(sizeof(privateDtw_cJSON_element_and_key));
    created->key = formmate_args->key_provider_callback(item,args);
    created->free_key = formmate_args->free_key;
    created->element =formmate_args->callback(item,formmate_args->args);
    return (void*)created;
}

bool private_dtw_cJSONObject_filtrage(DtwResource *item,void *args) {
    DtwResourcecJSONObjectMapProps *formmate_args = (DtwResourcecJSONObjectMapProps*)args;
    return formmate_args->filtrage_callback(item,formmate_args->args);
}

int private_dtw_cJSONObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) {
    DtwResourcecJSONObjectMapProps *formmate_args = (DtwResourcecJSONObjectMapProps*)args;
    return formmate_args->ordenation_callback(item1,item2,formmate_args->args);
}

void privateDtwResource_add_to_item_to_cJSONObject(void* object, void *item){
    privateDtw_cJSON_element_and_key *casted = (privateDtw_cJSON_element_and_key*)item;
    cJSON_AddItemToObject((cJSON*)object,casted->key,casted->element);
    if(casted->free_key){
        free(casted->key);
    }
    free(casted);
}


cJSON *DtwResource_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props){

    cJSON *itens = cJSON_CreateObject();

    DtwResourceMapProps map_props = DtwResource_create_map_props(
        itens,
        privateDtwResource_add_to_item_to_cJSONObject,
        private_dtw_cJSONObject_callback
    );
    map_props.args = (void*)&props;
    if(props.filtrage_callback) {
        map_props.filtrage_callback = private_dtw_cJSONObject_filtrage;
    }

    if(props.ordenation_callback) {
        map_props.ordenation_callback = private_dtw_cJSONObject_ordenation;
    }

    DtwResource_map(self,map_props);

    return itens;
}

cJSON *DtwResource_schema_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props){
    if(self->schema_type != PRIVATE_DTW_SCHEMA_ROOT){
            private_DtwResource_raise_error(
                    self,
                    DTW_RESOURCE_ONLY_ROOT_SCHEMA_HAVE_SCHEMA_VALUES,
                    "only root schema have schema values"
            );
            return NULL;
    }
    return  DtwResource_map_cJSONObject(self->values_resource,props);
}
