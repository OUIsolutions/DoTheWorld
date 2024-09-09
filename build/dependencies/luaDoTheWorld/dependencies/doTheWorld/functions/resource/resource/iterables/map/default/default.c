#include "../unique.definition_requirements.h"
#include <time.h>
DtwResourceMapProps DtwResource_create_map_props(
    void *main_array,
    void(*append)(void *main_array_arg, void *item),
    void *(*callback)(DtwResource *item, void *args)
){
    DtwResourceMapProps props = {0};
    props.main_array = main_array;
    props.append = append;
    props.callback = callback;
    props.qtd = DTW_RESOURCE_ALL;
    return  props;
}

int  private_dtwResource_compare(const void *item1,const void*item2){
    privateDtwResource_map_element *item1_converted = *(privateDtwResource_map_element**)item1;
    privateDtwResource_map_element *item2_converted = *(privateDtwResource_map_element**)item2;

    return item1_converted->ordenation_callback(item1_converted->current,item2_converted->current,item1_converted->args);
}

void DtwResource_map(DtwResource *self,DtwResourceMapProps props){
    //printf("%p\n",ordenation_callback);
    DtwResourceArray *itens = DtwResource_sub_resources(self);
    privateDtwResource_map_element **mapped_elements= NULL;
    int total_mapped_elements = 0;
    if(props.ordenation_callback) {
        mapped_elements = (privateDtwResource_map_element**)malloc(
            (itens->size+1) * sizeof(privateDtwResource_map_element**)
            );
    }

    int total = 0;
    int total_skipded = 0;
    for(int i = 0; i < itens->size; i++){
        DtwResource *current = itens->resources[i];

        if(props.filtrage_callback){
            bool result = props.filtrage_callback(current, props.args);
            if(!result){
                continue;
            }
        }

        total_skipded++;

        if(total_skipded <= props.start){
            continue;
        }

        if(total + 1 > props.qtd && props.qtd != -1){
            break;
        }

        void* result = props.callback(current, props.args);

        if(result == NULL){
            continue;
        }
        total+=1;

        if(props.ordenation_callback == NULL) {

            props.append(props.main_array,result);
        }

        if(props.ordenation_callback){
            privateDtwResource_map_element *created  = (privateDtwResource_map_element*)malloc(sizeof(privateDtwResource_map_element));
            *created = (privateDtwResource_map_element){0};
            created->result = result;
            created->current = current;
            created->ordenation_callback = props.ordenation_callback;
            created->args =props.args;
          //  printf("criado %p\n",created);
            mapped_elements[total_mapped_elements] = created;
            total_mapped_elements+=1;
        }

    }

    if(props.ordenation_callback) {

        qsort(
            mapped_elements,
            total_mapped_elements,
            sizeof(privateDtwResource_map_element*),
            private_dtwResource_compare
            );

        for(int i = 0; i< total_mapped_elements; i++) {
            privateDtwResource_map_element *current = mapped_elements[i];
            props.append(props.main_array,current->result);
            free(current);
        }
        free(mapped_elements);
    }


}
void DtwResource_schema_map(DtwResource *self,DtwResourceMapProps props){

    if(self->schema_type != PRIVATE_DTW_SCHEMA_ROOT){
            private_DtwResource_raise_error(
                    self,
                    DTW_RESOURCE_ONLY_ROOT_SCHEMA_HAVE_SCHEMA_VALUES,
                    "only root schema have schema values"
            );
            return ;
        }

     DtwResource_map(self->values_resource, props);
}
