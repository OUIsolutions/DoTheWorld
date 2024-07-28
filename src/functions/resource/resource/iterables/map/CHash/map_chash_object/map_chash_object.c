#define DTW_ALLOW_CHASH
#include "../unique.definition_requirements.h"

void  *private_dtw_CHashObject_callback(DtwResource *item,void *args) {
    private_DtwResource_CHashObject_args *formmate_args = (private_DtwResource_CHashObject_args*)args;
    privateDtw_CHash_element_and_key *created = (privateDtw_CHash_element_and_key*)malloc(sizeof(privateDtw_CHash_element_and_key));
    created->key = formmate_args->key_provider(item,args);
    created->element =formmate_args->callback(item,formmate_args->args);
    return (void*)created;
}

bool private_dtw_CHashObject_filtrage(DtwResource *item,void *args) {
    private_DtwResource_CHashObject_args *formmate_args = (private_DtwResource_CHashObject_args*)args;
    return formmate_args->filtrage(item,formmate_args->args);
}

int private_dtw_CHashObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) {
    private_DtwResource_CHashObject_args *formmate_args = (private_DtwResource_CHashObject_args*)args;
    return formmate_args->ordenation(item1,item2,formmate_args->args);
}

void privateDtwResource_add_to_item_to_CHashObject(void* object, void *item){
    privateDtw_CHash_element_and_key *casted = (privateDtw_CHash_element_and_key*)item;
    CHashObject_set_many((CHash*)object,casted->key,casted->element);
    free(casted->key);
    free(casted);
}


CHash *DtwResource_map_CHashObject(DtwResource *self,
char *(*key_provider_callback)(DtwResource *item,void *args),
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
CHash *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd){

    CHash *itens = newCHashObjectEmpty();
    private_DtwResource_CHashObject_args formated_args = {0};
    formated_args.callback = callback;
    formated_args.filtrage = filtrage_callback;
    formated_args.key_provider = key_provider_callback;
    formated_args.ordenation = ordenation_callback;
    formated_args.args = args;

    bool (*filtrage)(DtwResource *,void *) = NULL;
    if(filtrage_callback) {
        filtrage = private_dtw_CHashObject_filtrage;
    }
    int (*ordenation)(DtwResource *,DtwResource *,void *) = NULL;
    if(ordenation_callback) {
        ordenation = private_dtw_CHashObject_ordenation;
    }

    DtwResource_map(self,
        itens,
        privateDtwResource_add_to_item_to_CHashObject,
        filtrage,
        ordenation,
        private_dtw_CHashObject_callback,
        &formated_args,
        start,
        qtd
        );

    return itens;
}
