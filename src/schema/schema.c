


DtwSchema * newDtwSchema(const char *path){
    DtwSchema *schema = (DtwSchema*) malloc(sizeof(DtwSchema));
    *schema = (DtwSchema){0};

    //make both reference each other
    DtwResource *master = new_DtwResource(path);
    master->schema = schema;
    schema->master = master;

    schema->master->schema = schema;
    schema->values_resource = DtwResource_sub_resource(master,"%s",DTW_SCHEMA_VALUES_NAME);
    schema->index_resource = DtwResource_sub_resource(master,"%s",DTW_SCHEMA_INDEX_NAME);
    schema->primary_keys = newDtwStringArray();
    return schema;
}

void DtwSchema_free(DtwSchema *self){
    if(self->owner){
        //the resource call the privateDtwSchema_free_self_props, and frees
        //everything
        DtwResource_free(self->master);
    }

}


void privateDtwSchema_free_self_props(DtwSchema *self){
    DtwStringArray_free(self->primary_keys);
    free(self);
}


DtwResource * DtwSchema_new_insertion(DtwSchema *schema){
    DtwResource  *created = DtwResource_sub_resource_random(schema->values_resource,NULL);
    return created;
}

DtwResourceArray * DtwSchema_get_values(DtwSchema *schema){
    return DtwResource_sub_resources(schema->values_resource);
}

DtwResource * DtwSchema_find_by_primary_key_with_any(DtwSchema *schema,const char *primary_key,unsigned  char *value,long size){
    DtwResource *primary_key_folder = DtwResource_sub_resource(schema->values_resource,"%s",primary_key);
    char *sha = dtw_generate_sha_from_any(value,size);
    DtwResource *index_value = DtwResource_sub_resource(primary_key_folder,"%s",sha);
    free(sha);
    if(DtwResource_type(index_value) == DTW_NOT_FOUND){
        return NULL;
    }
    char *element_folder = DtwResource_get_string(index_value);
    if(DtwResource_error(schema->master)){
        return NULL;
    }
    if(!element_folder){
        return NULL;
    }
    DtwResource *founded_resource = DtwResource_sub_resource(schema->values_resource,"%s",element_folder);
    return founded_resource;
}

DtwResource * DtwSchema_find_by_primary_key_with_string(DtwSchema *schema,const char *key,const char *value){
    return DtwSchema_find_by_primary_key_with_any(
            schema,
            key,
            (unsigned  char *)value,
            (long )strlen(value)
            );
}


