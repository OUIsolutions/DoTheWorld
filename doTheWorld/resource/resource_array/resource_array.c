


DtwResourceArray * newDtwResourceArray(){
    DtwResourceArray *self = (DtwResourceArray*) malloc(sizeof (DtwResourceArray));
    self->resources = (DtwResource**) malloc(0);
    self->size = 0;
    return self;
}


void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element){
    self->resources = realloc(self->resources,(self->size +1) * sizeof (DtwResource**));
    self->resources[self->size] = element;
    self->size+=1;
}


DtwResource* DtwResourceArray_get_by_name(DtwResourceArray *self, const char *name){
    for(int i = 0; i < self->size; i++){
        DtwResource *current = self->resources[i];
        if(strcmp(current->name,name) ==0){
            return current;
        }
    }
    return NULL;
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


void DtwResourceArray_represent(DtwResourceArray *self){
    for(int i = 0; i< self->size; i++){
        printf("----------------------------------------\n");
        DtwResource_represent(self->resources[i]);
    }
}

void DtwResourceArray_free(DtwResourceArray *self){
    for(int i = 0; i < self->size; i++){
        DtwResource_free(self->resources[i]);
    }
    free(self->resources);
    free(self);
}
