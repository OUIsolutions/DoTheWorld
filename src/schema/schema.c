


DtwSchema * newDtwSchema(const char *path){
    DtwSchema *schema = (DtwSchema*) malloc(sizeof(DtwSchema));
    *schema = (DtwSchema){0};

    //make both reference each other
    DtwResource *master = new_DtwResource(path);
    master->schema = schema;
    schema->master = master;

    schema->master->schema = schema;
    schema->values_resource = DtwResource_sub_resource(master,"%s",DTW_SCHEMA_VALUES_NAME);
    schema->values_resource->its_value_folder = true;
    schema->index_resource = DtwResource_sub_resource(master,"%s",DTW_SCHEMA_INDEX_NAME);
    schema->primary_keys = newDtwStringArray();

    return schema;
}

void DtwSchema_add_primary_key(DtwSchema *self,const char *primary_key){
    if(privateDtwSchema_error(self)){
        return ;
    }
    bool not_found =DtwStringArray_find_position(self->primary_keys,primary_key)==-1;

    if(not_found){
        DtwStringArray_append(self->primary_keys,primary_key);
    }
}

void DtwSchema_free(DtwSchema *self){
    if(privateDtwSchema_error(self)){
        return;
    }
    if(self->owner){
        //the resource call the privateDtwSchema_free_self_props, and frees
        //everything
        DtwResource_free(self->master);
    }

}
bool privateDtwSchema_error(DtwSchema *self){
    if(!self){
        return true;
    }
    if(DtwResource_error(self->master)){
        return true;
    }
    return false;
}

void privateDtwSchema_free_self_props(DtwSchema *self){
    DtwStringArray_free(self->primary_keys);
    free(self);
}


DtwResource * DtwSchema_new_insertion(DtwSchema *schema){
    if(privateDtwSchema_error(schema)){
        return NULL;
    }
    DtwResource  *created = DtwResource_sub_resource_random(schema->values_resource,NULL);

    return created;
}

DtwResourceArray * DtwSchema_get_values(DtwSchema *self){
    if(privateDtwSchema_error(self)){
        return NULL;
    }
    return DtwResource_sub_resources(self->values_resource);
}

DtwResource * DtwSchema_find_by_primary_key_with_binary(DtwSchema *self, const char *primary_key, unsigned  char *value, long size){
    if(privateDtwSchema_error(self)){
        return NULL;
    }
    DtwResource *primary_key_folder = DtwResource_sub_resource(self->index_resource, "%s", primary_key);
    char *sha = dtw_generate_sha_from_any(value,size);
    DtwResource *index_value = DtwResource_sub_resource(primary_key_folder,"%s",sha);
    free(sha);
    if(DtwResource_type(index_value) == DTW_NOT_FOUND){
        return NULL;
    }
    char *element_folder = DtwResource_get_string(index_value);
    if(DtwResource_error(self->master)){
        return NULL;
    }
    if(!element_folder){
        return NULL;
    }
    DtwResource *founded_resource = DtwResource_sub_resource(self->values_resource, "%s", element_folder);
    return founded_resource;
}

DtwResource * DtwSchema_find_by_primary_key_with_string(DtwSchema *self, const char *key, const char *value){
    if(privateDtwSchema_error(self)){
        return NULL;
    }
    return DtwSchema_find_by_primary_key_with_binary(
            self,
            key,
            (unsigned char *) value,
            (long) strlen(value)
    );
}


