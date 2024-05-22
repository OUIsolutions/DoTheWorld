


DtwOldSchema * newDtwSchema(const char *path){
    DtwOldSchema *schema = (DtwOldSchema*) malloc(sizeof(DtwOldSchema));
    *schema = (DtwOldSchema){0};

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

void DtwSchema_add_primary_key(DtwOldSchema *self, const char *primary_key){
    if(privateDtwSchema_error(self)){
        return ;
    }
    bool not_found =DtwStringArray_find_position(self->primary_keys,primary_key)==-1;

    if(not_found){
        DtwStringArray_append(self->primary_keys,primary_key);
    }
}

void DtwSchema_free(DtwOldSchema *self){
    if(privateDtwSchema_error(self)){
        return;
    }
    if(self->owner){
        //the resource call the privateDtwSchema_free_self_props, and frees
        //everything
        DtwResource_free(self->master);
    }

}
bool privateDtwSchema_error(DtwOldSchema *self){
    if(!self){
        return true;
    }
    if(DtwResource_error(self->master)){
        return true;
    }
    return false;
}

void privateDtwSchema_free_self_props(DtwOldSchema *self){
    DtwStringArray_free(self->primary_keys);
    free(self);
}


DtwResource * DtwSchema_new_insertion(DtwOldSchema *schema){
    if(privateDtwSchema_error(schema)){
        return NULL;
    }
    DtwResource  *created = DtwResource_sub_resource_random(schema->values_resource,NULL);

    return created;
}

DtwResourceArray * DtwSchema_get_values(DtwOldSchema *self){
    if(privateDtwSchema_error(self)){
        return NULL;
    }
    return DtwResource_sub_resources(self->values_resource);
}

DtwResource * DtwSchema_find_by_primary_key_with_binary(DtwOldSchema *self, const char *primary_key, unsigned  char *value, long size){
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

DtwResource * DtwSchema_find_by_primary_key_with_string(DtwOldSchema *self, const char *key, const char *value){
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



void DtwSchema_commit(DtwOldSchema *self){
    if(privateDtwSchema_error(self)){
        return;
    }
    DtwResource_commit(self->master);
}

DtwResource  *DtwSchema_get_find_by_nameID(DtwOldSchema *self, const char *name){
    if(privateDtwSchema_error(self)){
        return NULL;
    }

    DtwResource *element = DtwResource_sub_resource(self->values_resource,name);
    return element;
}

void DtwSchema_dangerours_remove_prop(DtwOldSchema *self, const char *prop){

    bool allow_transaction = self->master->allow_transaction;
    DtwResourceArray * all_values = DtwResource_sub_resources(self->values_resource);
    DtwTransaction * transaction = self->master->root_props->transaction;
    for(int i = 0; i < all_values->size; i++){
        DtwResource *current = all_values->resources[i];
        DtwResource *prop_to_remove = DtwResource_sub_resource(current,"%s",prop);
        if(allow_transaction){
            DtwTransaction_delete_any(transaction,prop_to_remove->path);
        }else{
            dtw_remove_any(prop_to_remove->path);
        }

    }
    DtwResource *index_element = DtwResource_sub_resource(self->index_resource,"%s",prop);
    if(allow_transaction){
        DtwTransaction_delete_any(transaction,index_element->path);
    }else{
        dtw_remove_any(index_element->path);
    }
}


void DtwSchema_dangerours_rename_prop(DtwOldSchema *self, const char *prop, const char *new_name){
    bool allow_transaction = self->master->allow_transaction;
    DtwResourceArray * all_values = DtwResource_sub_resources(self->values_resource);
    DtwTransaction * transaction = self->master->root_props->transaction;
    for(int i = 0; i < all_values->size; i++){
        DtwResource *current = all_values->resources[i];
        DtwResource *prop_to_remove = DtwResource_sub_resource(current,"%s",prop);
        DtwResource *new_prop = DtwResource_sub_resource(current,"%s",new_name);
        if(allow_transaction){
            DtwTransaction_move_any_merging(transaction,prop_to_remove->path,new_prop->path);
        }else{
            dtw_move_any(prop_to_remove->path,new_prop->path,DTW_MERGE);
        }

    }
    DtwResource *index_element = DtwResource_sub_resource(self->index_resource,"%s",prop);
    DtwResource *new_index = DtwResource_sub_resource(self->index_resource,"%s",new_name);
    if(allow_transaction){
        DtwTransaction_move_any_merging(transaction,index_element->path,new_index->path);
    }else{
        dtw_move_any(index_element->path,new_index->path,DTW_MERGE);
    }
}
