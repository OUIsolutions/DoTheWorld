#define DTW_ALLOW_CHASH
#include "../unique.definition_requirements.h"

DtwResourceCHashObjectMapProps DtwResource_createCHashObjectMapProps(
    CHash *(*callback)(DtwResource *item, void *args),
    char* (*key_provider)(DtwResource *item, void *args_filter)
){
    DtwResourceCHashObjectMapProps props = {0};
    props.qtd = DTW_RESOURCE_ALL;
    props.callback = callback;
    props.key_provider_callback = key_provider;
    return props;
}


void  *private_dtw_CHashObject_callback(DtwResource *item,void *args) {
    DtwResourceCHashObjectMapProps *formmate_args = (DtwResourceCHashObjectMapProps*)args;
    privateDtw_CHash_element_and_key *created = (privateDtw_CHash_element_and_key*)malloc(sizeof(privateDtw_CHash_element_and_key));
    created->free_key = formmate_args->free_key;
    created->key = formmate_args->key_provider_callback(item,args);
    created->element =formmate_args->callback(item,formmate_args->args);
    return (void*)created;
}

bool private_dtw_CHashObject_filtrage(DtwResource *item,void *args) {
    DtwResourceCHashObjectMapProps *formmate_args = (DtwResourceCHashObjectMapProps*)args;
    return formmate_args->filtrage_callback(item,formmate_args->args);
}

int private_dtw_CHashObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) {
    DtwResourceCHashObjectMapProps *formmate_args = (DtwResourceCHashObjectMapProps*)args;
    return formmate_args->ordenation_callback(item1,item2,formmate_args->args);
}

void privateDtwResource_add_to_item_to_CHashObject(void* object, void *item){
    privateDtw_CHash_element_and_key *casted = (privateDtw_CHash_element_and_key*)item;
    CHashObject_set_any((CHash*)object,casted->key,casted->element);
    if(casted->free_key){
        free(casted->key);
    }

    free(casted);
}


CHash *DtwResource_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props){

    CHash *itens = newCHashObjectEmpty();

    DtwResourceMapProps map_props = DtwResource_create_map_props(
        itens,
        privateDtwResource_add_to_item_to_CHashObject,
        private_dtw_CHashObject_callback
    );
    map_props.args = (void*)&props;
    if(props.filtrage_callback) {
        map_props.filtrage_callback = private_dtw_CHashObject_filtrage;
    }

    if(props.ordenation_callback) {
        map_props.ordenation_callback = private_dtw_CHashObject_ordenation;
    }
    DtwResource_map(self,map_props);

    return itens;
}

CHash *DtwResource_schema_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props){
    if(self->schema_type != PRIVATE_DTW_SCHEMA_ROOT){
            private_DtwResource_raise_error(
                    self,
                    DTW_RESOURCE_ONLY_ROOT_SCHEMA_HAVE_SCHEMA_VALUES,
                    "only root schema have schema values"
            );
            return NULL;
    }
    return DtwResource_map_CHashObject(self->values_resource,props);
}
