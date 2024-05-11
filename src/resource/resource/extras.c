


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


void DtwResource_destroy(DtwResource *self){
    if(DtwResource_error(self)){
        return ;
    }
    if(self->allow_transaction){
        DtwTransaction_delete_any(self->root_props->transaction,self->path);
    }
    else{
        dtw_remove_any(self->path);
    }

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

