


bool DtwResource_error(DtwResource *self){
    if(!self){
        return true;
    }
    if(DtwResource_get_error_code(self) == DTW_RESOURCE_OK){
        return false;
    }
    return true;
}

int DtwResource_get_error_code(DtwResource *self){
    if(!self){
        return DTW_RESOURCE_ELEMENT_IS_NULL;
    }
    return self->root_props->error_code;
}

char * DtwResource_get_error_message(DtwResource *self){

    if(!self){
        return (char*)"element its null";
    }

    return self->root_props->error_message;
}
void  DtwResource_clear_errors(DtwResource *self){
    if(!DtwResource_error(self)){
        return;
    }
    free(self->root_props->error_message);
    self->root_props->error_message = NULL;
    free(self->root_props->error_path);
    self->root_props->error_path = NULL;
    self->root_props->error_code = DTW_RESOURCE_OK;

}

void  private_DtwResource_raise_error(DtwResource *self, int error_code, const char *error_message){
    self->root_props->error_code = error_code;
    self->root_props->error_path = strdup(self->path);
    self->root_props->error_message = dtw_replace_string(error_message,"#path#",self->path);

}

void DtwResource_rename(DtwResource *self,const char *new_name){

    char *old_path = strdup(self->path);
    free(self->path);
    self->path  = dtw_concat_path(self->mother->path, new_name);

    if(self->allow_transaction){
        DtwTransaction_move_any(self->root_props->transaction,old_path,self->path);
    }
    else{
        dtw_move_any(old_path,self->path,DTW_NOT_MERGE);
    }
    free(old_path);

}


int DtwResource_lock(DtwResource *self){
    if(DtwResource_error(self)){
        return -1;
    }
    return DtwLocker_lock(self->root_props->locker, self->path);
}

void DtwResource_unlock(DtwResource *self){
    if(DtwResource_error(self)){
        return ;
    }
    DtwLocker_unlock(self->root_props->locker, self->path);
    
}
void private_DtwResurce_destroy_primary_key(DtwResource *self,void *vschma,const char *current_pk) {

    DtwSchema  *schema = (DtwSchema*)vschma;

    DtwResource *possible_pk = DtwResource_sub_resource(self, "%s", current_pk);
    if (!DtwResource_is_file(possible_pk)) {
        return;
    }
    DtwResource *pk_index_folder = DtwResource_sub_resource(schema->index_resource, "%s", current_pk);
    long size;
    bool is_binary;
    unsigned char *possible_pk_value = DtwResource_get_any(possible_pk, &size, &is_binary);
    char *pk_sha = dtw_generate_sha_from_any(possible_pk_value, size);

    DtwResource *pk_index_value = DtwResource_sub_resource(pk_index_folder, "%s", pk_sha);

    if (self->allow_transaction) {
        DtwTransaction_delete_any(self->root_props->transaction, pk_index_value->path);
    } else {
        dtw_remove_any(pk_index_value->path);
    }


}
void private_DtwResource_destroy_all_primary_keys(DtwResource *self,void *vschema){
    DtwSchema *schema = (DtwSchema*)vschema;
    for(int i = 0; i < schema->primary_keys->size; i++){
        char *current_pk = schema->primary_keys->strings[i];
        private_DtwResurce_destroy_primary_key(self,schema,current_pk);
    }
}
void DtwResource_destroy(DtwResource *self){
    if(DtwResource_error(self)){
        return;
    }
    DtwSchema * schema = (DtwSchema*)self->mother->mother->schema;

    if(schema != NULL){
        private_DtwResource_destroy_all_primary_keys(self,schema);
    }


    if(self->allow_transaction){
        DtwTransaction_delete_any(self->root_props->transaction,self->path);
    }
    else{
        dtw_remove_any(self->path);
    }

}


DtwSchema * DtwResource_sub_schema(DtwResource *self, const char *format,...){

    DtwSchema *schema = (DtwSchema*) malloc(sizeof(DtwSchema));
    *schema = (DtwSchema){0};

    va_list args;
    va_start(args, format);
    char *name = private_dtw_format_vaarg(format,args);
    va_end(args);

    //make both reference each other
    DtwResource *master =DtwResource_sub_resource(self,"%s",name);
    free(name);
    master->schema = schema;
    schema->master = master;

    schema->master->schema = schema;
    schema->values_resource = DtwResource_sub_resource(master,"%s",DTW_SCHEMA_VALUES_NAME);
    schema->index_resource = DtwResource_sub_resource(master,"%s",DTW_SCHEMA_INDEX_NAME);
    schema->primary_keys = newDtwStringArray();
    return schema;
}

void DtwResource_commit(DtwResource *self){
    if(DtwResource_error(self)){
        return ;
    }
    DtwTransaction_commit(self->root_props->transaction,NULL);
}

long DtwResource_size(DtwResource *self){
    if(DtwResource_error(self)){
        return -1;
    }
    return dtw_get_total_itens_of_dir(self->path);
}



DtwStringArray *DtwResource_list_names(DtwResource *self){
    if(DtwResource_error(self)){
        return NULL;
    }
    return dtw_list_all(self->path,DTW_NOT_CONCAT_PATH);
}

int DtwResource_type(DtwResource *self){
    if(DtwResource_error(self)){
        return -1;
    }
    DtwResource_load_if_not_loaded(self);

    if(!self->value_any){
        return dtw_entity_type(self->path);
    }


    if(self->is_binary){
        return DTW_COMPLEX_BINARY;
    }
    char *data_in_string = DtwResource_get_string(self);

    if(
            strcmp(data_in_string,"t") == 0 || strcmp(data_in_string,"true") == 0  ||
                    strcmp(data_in_string,"f") == 0 || strcmp(data_in_string,"false") == 0

    ){
        return DTW_COMPLEX_BOOL_TYPE;
    }


    double data_double;
    int result = sscanf(data_in_string,"%lf",&data_double);
    if(result == 0){
        return DTW_COMPLEX_STRING_TYPE;

    }


    for(int i = 0; i < self->value_size; i++){
        char current = data_in_string[i];
        if(current == '.'){
            return  DTW_COMPLEX_DOUBLE_TYPE;
        }
    }
    return  DTW_COMPLEX_LONG_TYPE;

}
bool DtwResource_is_file(DtwResource *self){
    if(DtwResource_error(self)){
        return -1;
    }
    DtwResource_load_if_not_loaded(self);

    if(self->value_any){
        return true;
    }
    return  false;

}

const char * DtwResource_type_in_str(DtwResource *self){
    if(DtwResource_error(self)){
        return NULL;
    }
     return dtw_convert_entity(DtwResource_type(self));
}

void DtwResource_represent(DtwResource *self){
    if(DtwResource_error(self)){
        printf("error code: %d\n", DtwResource_get_error_code(self));
        printf("error message: %s\n", DtwResource_get_error_message(self));
        return ;
    }

    printf("path: %s\n", self->path);
    printf("name: %s\n",self->name);
    if(self->loaded){
        printf("type: %s\n",DtwResource_type_in_str(self));
        int type = DtwResource_type(self);
        if(type == DTW_COMPLEX_STRING_TYPE){
            printf("value: %s\n", DtwResource_get_string(self));
        }
        if(type == DTW_COMPLEX_LONG_TYPE){
            printf("value: %ld\n", DtwResource_get_long(self));
        }

        if(type == DTW_COMPLEX_DOUBLE_TYPE){
            printf("value: %lf\n", DtwResource_get_double(self));
        }

        if(type == DTW_COMPLEX_BOOL_TYPE){
            printf("value: %s\n",DtwResource_get_bool(self) ?"true": "false");
        }

    }


}

