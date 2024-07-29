#include "../unique.definition_requirements.h"

void  *private_dtw_cJSONArray_callback(DtwResource *item,void *args) {
    DtwResourcecJSONArrayMapProps *formmate_args = (DtwResourcecJSONArrayMapProps*)args;
    return (void*)formmate_args->callback(item,formmate_args->args);
}

bool private_dtw_cJSONArray_filtrage(DtwResource *item,void *args) {
    DtwResourcecJSONArrayMapProps *formmate_args = (DtwResourcecJSONArrayMapProps*)args;
    return formmate_args->filtrage_callback(item,formmate_args->args);
}

int private_dtw_cJSONArray_ordenation(DtwResource *item1,DtwResource *item2,void *args) {
    DtwResourcecJSONArrayMapProps *formmate_args = (DtwResourcecJSONArrayMapProps*)args;
    return formmate_args->ordenation_callback(item1,item2,formmate_args->args);
}

void privateDtwResource_add_to_item_to_cJSONArray_array(void* array, void *item){
    cJSON_AddItemToArray((cJSON *)array, (cJSON *)item);
}

cJSON *DtwResource_map_cJSONArray(DtwResource *self,DtwResourcecJSONArrayMapProps props){

    cJSON *itens = cJSON_CreateArray();
    DtwResourceMapProps mapped_props = DtwResource_create_map_props(
        itens,
        privateDtwResource_add_to_item_to_cJSONArray_array,
        private_dtw_cJSONArray_callback
    );
    mapped_props.filtrage_callback = private_dtw_cJSONArray_filtrage;
    mapped_props.ordenation_callback = private_dtw_cJSONArray_ordenation;

    DtwResource_map(self,mapped_props);

    return itens;
}