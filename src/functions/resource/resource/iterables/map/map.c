#include "../unique.definition_requirements.h"

int  private_dtwResource_compare(const void *item1,const void*item2){
    privateDtwResource_map_element *item1_converted = *(privateDtwResource_map_element**)item1;
    privateDtwResource_map_element *item2_converted = *(privateDtwResource_map_element**)item2;

    return item1_converted->ordenation_callback(item1_converted->current,item2_converted->current,item1_converted->args);
}

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
    //printf("%p\n",ordenation_callback);
    DtwResourceArray *itens = DtwResource_sub_resources(self);
    privateDtwResource_map_element **mapped_elements= NULL;
    int total_mapped_elements = 0;
    if(ordenation_callback) {
        mapped_elements = (privateDtwResource_map_element**)malloc(
            (itens->size+1) * sizeof(privateDtwResource_map_element**)
            );
    }



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

        if(result && ordenation_callback == NULL) {

            append(main_array,result);
        }

        if(result && ordenation_callback){
            privateDtwResource_map_element *created  = (privateDtwResource_map_element*)malloc(sizeof(privateDtwResource_map_element));
            *created = (privateDtwResource_map_element){0};
            created->result = result;
            created->current = current;
            created->ordenation_callback = ordenation_callback;
            created->args =args;
          //  printf("criado %p\n",created);
            mapped_elements[total_mapped_elements] = created;
            total_mapped_elements+=1;
        }

    }

    if(ordenation_callback) {

        qsort(
            mapped_elements,
            total_mapped_elements,
            sizeof(privateDtwResource_map_element*),
            private_dtwResource_compare
            );

        for(int i = 0; i< total_mapped_elements; i++) {
            privateDtwResource_map_element *current = mapped_elements[i];
            append(main_array,current->result);
            free(current);
        }
        free(mapped_elements);
    }


}
