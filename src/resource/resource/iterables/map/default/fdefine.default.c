//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../../../imports/imports.dep_define.h"
//silver_chain_scope_end



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
    if(DtwResource_error(self)){
        return;
    }

    DtwResourceArray *itens = NULL;
    privateDtwSchemaUnsafe({
        itens = DtwResource_sub_resources(self);
    })

    if(DtwResource_error(self)){
        return;
    }

    privateDtwResource_map_element **mapped_elements= NULL;
    int total_mapped_elements = 0;
    
    // Perform ordering before the main loop
    if(props.ordenation_callback) {
        mapped_elements = (privateDtwResource_map_element**)malloc(
            (itens->size+1) * sizeof(privateDtwResource_map_element**)
        );
        
        // First, collect all elements for ordering
        for(int i = 0; i < itens->size; i++){
            DtwResource *current = itens->resources[i];
            
            if(props.filtrage_callback){
                bool result = props.filtrage_callback(current, props.args);
                if(DtwResource_error(self)){
                    return;
                }
                if(!result){
                    continue;
                }
            }
            
            privateDtwResource_map_element *created = (privateDtwResource_map_element*)malloc(sizeof(privateDtwResource_map_element));
            *created = (privateDtwResource_map_element){0};
            created->current = current;
            created->ordenation_callback = props.ordenation_callback;
            created->args = props.args;
            mapped_elements[total_mapped_elements] = created;
            total_mapped_elements++;
        }
        
        // Sort the elements
        qsort(
            mapped_elements,
            total_mapped_elements,
            sizeof(privateDtwResource_map_element*),
            private_dtwResource_compare
        );
    }

    int total = 0;
    int total_skipded = 0;
    
    if(props.ordenation_callback) {
        // Process sorted elements
        for(int i = 0; i < total_mapped_elements; i++){
            if(i < props.start){
                continue;
            }
            
            if(total >= props.qtd && props.qtd != -1){
                break;
            }
            
            privateDtwResource_map_element *element = mapped_elements[i];
            void* result = props.callback(element->current, props.args);
            
            if(DtwResource_error(self)){
                if(result){
                    props.append(props.main_array, result);
                }
                // Clean up
                for(int j = i; j < total_mapped_elements; j++){
                    free(mapped_elements[j]);
                }
                free(mapped_elements);
                return;
            }
            
            if(result != NULL){
                props.append(props.main_array, result);
                if(DtwResource_error(self)){
                    // Clean up
                    for(int j = i; j < total_mapped_elements; j++){
                        free(mapped_elements[j]);
                    }
                    free(mapped_elements);
                    return;
                }
                total++;
            }
        }
        
        // Clean up
        for(int i = 0; i < total_mapped_elements; i++){
            free(mapped_elements[i]);
        }
        free(mapped_elements);
    }
    else {
        // Original logic for non-sorted processing
        for(int i = 0; i < itens->size; i++){
            DtwResource *current = itens->resources[i];

            if(props.filtrage_callback){
                bool result = props.filtrage_callback(current, props.args);
                if(DtwResource_error(self)){
                    return;
                }
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
            if(DtwResource_error(self)){
                if(result){
                    props.append(props.main_array,result);
                }
                return;
            }
            if(result == NULL){
                continue;
            }
            
            props.append(props.main_array,result);
            if(DtwResource_error(self)){
                return;
            }
            total++;
        }
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
