#define DTW_ALLOW_CHASH
#include "../unique.definition_requirements.h"

void  *private_dtw_CHashArray_callback(DtwResource *item,void *args) {
    private_DtwResource_CHashArray_args *formmate_args = (private_DtwResource_CHashArray_args*)args;

    return (void*)formmate_args->callback(item,formmate_args->args);
}

bool private_dtw_CHashArray_filtrage(DtwResource *item,void *args) {
    private_DtwResource_CHashArray_args *formmate_args = (private_DtwResource_CHashArray_args*)args;
    return formmate_args->filtrage(item,formmate_args->args);
}

int private_dtw_CHashArray_ordenation(DtwResource *item1,DtwResource *item2,void *args) {
    private_DtwResource_CHashArray_args *formmate_args = (private_DtwResource_CHashArray_args*)args;
    return formmate_args->ordenation(item1,item2,formmate_args->args);
}

void privateDtwResource_add_to_item_to_CHashArray_array(void* array, void *item){
    CHashArray_append_any(array, (CHash *)item);
}

CHashArray *DtwResource_map_CHashArray(DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
CHash *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd){

    CHashArray *itens = newCHashArrayEmpty();
    private_DtwResource_CHashArray_args formated_args = {0};
    formated_args.callback = callback;

    formated_args.filtrage = filtrage_callback;
    formated_args.ordenation = ordenation_callback;
    formated_args.args = args;

    bool (*filtrage)(DtwResource *,void *) = NULL;
    if(filtrage_callback) {
        filtrage = private_dtw_CHashArray_filtrage;
    }
    int (*ordenation)(DtwResource *,DtwResource *,void *) = NULL;
    if(ordenation_callback) {
        ordenation = private_dtw_CHashArray_ordenation;
    }

    DtwResource_map(self,
        itens,
        privateDtwResource_add_to_item_to_CHashArray_array,
        filtrage,
        ordenation,
        private_dtw_CHashArray_callback,
        &formated_args,
        start,
        qtd
        );

    return itens;
}
