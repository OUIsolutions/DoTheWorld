

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = (DtwResource*) malloc(sizeof (DtwResource));
    *self =(DtwResource){0};

    self->path = strdup(path);
    self->name = strdup(path);
    self->sub_resources = newDtwResourceArray();
    self->allow_transaction = true;
    self->use_locker_on_unique_values = true;
    self->cache_sub_resources = true;
    self->root_props = private_newDtwResourceRootProps();

    return self;
}   

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *format, ...){
    if(DtwResource_error(self)){
        return NULL;
    }

    if(private_dtw_resource_its_a_primary_key(self)){
        private_DtwResource_raise_error(
                self,
                DTW_RESOURCE_PRIMARY_KEY_CANNOT_HAVE_SUB_RESOURCE,
                "primary key %s cannot have a sub resource",
                self->name
        );
        return NULL;
    }

    va_list args;
    va_start(args, format);
    char *name = private_dtw_format_vaarg(format,args);
    va_end(args);


    DtwResource * Already_Exist = DtwResourceArray_get_by_name((DtwResourceArray*)self->sub_resources,name);
    if(Already_Exist){
        free(name);
        return Already_Exist;
    }

    DtwResource *new_element = (DtwResource*) malloc(sizeof (DtwResource));
    *new_element =(DtwResource){0};

    if(self->its_value_folder){
        new_element->its_a_element_folder = true;
    }
    if(self->its_a_element_folder){
        new_element->its_a_write_point =true;
    }


    new_element->allow_transaction = self->allow_transaction;
    new_element->use_locker_on_unique_values = self->use_locker_on_unique_values;
    new_element->root_props = self->root_props;
    //copied elements

    new_element->mother = self;
    new_element->path = dtw_concat_path(self->path, name);
    new_element->name = strdup(name);


    new_element->cache_sub_resources = self->cache_sub_resources;
    new_element->sub_resources = newDtwResourceArray();

    if(self->cache_sub_resources){
        DtwResourceArray_append((DtwResourceArray*)self->sub_resources,new_element);
    }
    free(name);
    return new_element;

}
DtwResource * DtwResource_sub_resource_ensuring_not_exist(DtwResource *self,const  char *format, ...){
    if(DtwResource_error(self)){
        return NULL;
    }
    va_list args;
    va_start(args, format);
    char *name = private_dtw_format_vaarg(format,args);
    va_end(args);
;

    DtwResource *possible_emptiy  = DtwResourceArray_get_by_name(
            (DtwResourceArray*)self->sub_resources,
            name
    );
    if(possible_emptiy){
        return NULL;
    }

    bool old_cache_value = self->cache_sub_resources;
    self->cache_sub_resources = false;
    possible_emptiy = DtwResource_sub_resource(self,"%s",name);
    possible_emptiy->cache_sub_resources = old_cache_value;
    self->cache_sub_resources = old_cache_value;
    if(self->use_locker_on_unique_values){
        DtwResource_lock(possible_emptiy);
    }

    int type = DtwResource_type(possible_emptiy);

    if(type == DTW_NOT_FOUND){


            if(self->cache_sub_resources){
                DtwResourceArray_append((DtwResourceArray*)self->sub_resources,possible_emptiy);
            }
            free(name);
            return possible_emptiy;
    }
    DtwResource_unlock(possible_emptiy);
    DtwResource_free(possible_emptiy);
    free(name);
    return  NULL;

}

void DtwResource_free(DtwResource *self){
    if(!self){
        return;
    }

    bool is_root = self->mother == NULL;
    if(is_root){
        privateDtwResourceRootProps_free(self->root_props);
    }
    if(self->schema){
        DtwSchema  *schema = (DtwSchema*)self->schema;
        privateDtwSchema_free_self_props(schema);
    }


    DtwResourceArray_free((DtwResourceArray*)self->sub_resources);



    if(self->value_any){
        free(self->value_any);
    }


    free(self->path);
    free(self->name);
    free(self);
}