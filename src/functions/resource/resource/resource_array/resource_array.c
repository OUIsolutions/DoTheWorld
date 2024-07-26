#include "../unique.definition_requirements.h"


DtwResourceArray * DtwResource_get_schema_values(DtwResource *self){
    if(DtwResource_error(self)){
        return NULL;
    }
    self->root_props->is_writing_schema = true;

    if(self->schema_type != PRIVATE_DTW_SCHEMA_ROOT){
        private_DtwResource_raise_error(
                self,
                DTW_RESOURCE_ONLY_ROOT_SCHEMA_HAVE_SCHEMA_VALUES,
                "only root schema have schema values"
        );
        return NULL;
    }

    DtwResourceArray *elements =  DtwResource_sub_resources(self->values_resource);
    self->root_props->is_writing_schema = false;
    return elements;
}


DtwResourceArray * DtwResource_sub_resources(DtwResource *self){


    DtwStringArray  *names  = DtwResource_list_names(self);
    DtwStringArray_sort(names);
    DtwResourceArray *target_array = (DtwResourceArray*)self->sub_resources;

    if(self->cache_sub_resources == false){
        target_array = newDtwResourceArray();
    }

    for(int i = 0; i < names->size; i++){
        char *current_name = names->strings[i];

        if(self->cache_sub_resources){
            DtwResource_sub_resource(self,"%s", current_name);
        }

        else{
            DtwResource *current_resource = DtwResource_sub_resource(self,"%s",current_name);
            DtwResourceArray_append(target_array,current_resource);
        }
    }

    DtwStringArray_free(names);
    return target_array;

}
