

void DtwResource_map(
DtwResource *self,
void *main_array,
void(*append)(void *main_array_arg, void *item),
bool(*filtrage_callback)(DtwResource *item, void *args),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
void *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd
){

    DtwResourceArray *itens = DtwResource_sub_resources(self);
    privateDtwResource_map_element **mapped_elements = (privateDtwResource_map_element**)malloc(
            (itens->size+1) * sizeof(privateDtwResource_map_element**)
            );

    int total_mapped_elements = 0;
    int total = 0;
    int total_skipded = 0;

    for(int i = 0; i < itens->size; i++){
        DtwResource *current = itens->resources[i];

        if(filtrage_callback){

            bool result = filtrage_callback(current, args);

            if(!result){
                continue;
            }
        }

        total_skipded++;

        if(total_skipded <= start){
            continue;
        }

        total+=1;
        if(total > qtd && qtd != -1){
            break;
        }

        void* result = callback(current, args);
        if(result){
            privateDtwResource_map_element *created  = (privateDtwResource_map_element*)malloc(sizeof(privateDtwResource_map_element));
            created->result = result;
            created->ordenation_callback = ordenation_callback;
            created->args =args;
            mapped_elements[total_mapped_elements] = created;
            total_mapped_elements+=1;
        }

    }
    for(int i = 0; i< total_mapped_elements; i++) {
        privateDtwResource_map_element *current = mapped_elements[i];
        append(main_array,current->result);
        free(current);
    }
    free(mapped_elements);

}
