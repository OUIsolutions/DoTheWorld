
#include "../unique.definition_requirements.h"

DtwResourceForeachProps DtwResource_create_foreach_props( void(*callback)(DtwResource *item, void *args)){
    DtwResourceForeachProps props = {0};
    props.callback = callback;
    props.qtd = DTW_RESOURCE_ALL;
    return props;
}

void DtwResource_foreach(DtwResource *self,DtwResourceForeachProps props){

    DtwResourceArray *itens = DtwResource_sub_resources(self);

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

        total++;

        if(total > props.qtd && props.qtd != -1){
            break;
        }

        props.callback(current, props.args);
    }
}

void DtwResource_schema_foreach(DtwResource *self,DtwResourceForeachProps props){

    if(self->schema_type != PRIVATE_DTW_SCHEMA_ROOT){
        private_DtwResource_raise_error(
                self,
                DTW_RESOURCE_ONLY_ROOT_SCHEMA_HAVE_SCHEMA_VALUES,
                "only root schema have schema values"
        );
        return ;
    }
    DtwResource_foreach(self->values_resource,props);
}
