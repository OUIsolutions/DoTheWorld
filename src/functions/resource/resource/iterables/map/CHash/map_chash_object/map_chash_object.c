#define DTW_ALLOW_CHASH
#include "../unique.definition_requirements.h"

void  *private_dtw_CHashObject_callback(DtwResource *item,void *args) {
    DtwResourceCHashObjectMapProps *formmate_args = (DtwResourceCHashObjectMapProps*)args;
    privateDtw_CHash_element_and_key *created = (privateDtw_CHash_element_and_key*)malloc(sizeof(privateDtw_CHash_element_and_key));
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
    CHashObject_set_many((CHash*)object,casted->key,casted->element);
    free(casted->key);
    free(casted);
}


CHash *DtwResource_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props){

    CHash *itens = newCHashObjectEmpty();

    DtwResourceMapProps map_props = DtwResource_create_map_props(
        itens,
        privateDtwResource_add_to_item_to_cJSONObject,
        private_dtw_CHashArray_callback
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
