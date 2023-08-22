

void DtwResource_unload(DtwResource *self){
    if(self->loaded == false){
        return;
    }
    if(self->value_any){
        free(self->value_any);
    }
    self->is_binary = false;
    self->value_size = 0;    
}

void DtwResource_load(DtwResource *self){

    DtwResource_unload(self);
    self->value_any = dtw_load_any_content(self->path,&self->value_size,&self->is_binary);
    self->loaded = true;

}
void DtwResource_load_if_not_loaded(DtwResource *self){
    if(self->loaded == false){
        DtwResource_load(self);
    }
}

/*
void DtwResource_load_content(DtwResource *self){
    DtwResource_unload_content(self);
    self->loaded = true;
    self->type  = dtw_entity_type(self->path);
    if(self->type != DTW_FILE_TYPE){
        return;
    }

    bool is_binary;
    long value_size;
    unsigned char *data  = dtw_load_any_content(self->path, &value_size, &is_binary);
    if(is_binary){
        self->type = DTW_COMPLEX_BINARY;
        self->value_size = value_size;
        self->value_any = data;
        return;
    }

    char *data_in_string = (char*)data;

     if(strcmp(data_in_string,"t") == 0 || strcmp(data_in_string,"true") == 0){
        self->type = DTW_COMPLEX_BOOL_TYPE;
        self->value_bool = true;
        free(data);
        return;
    }

    if(strcmp(data_in_string,"f") == 0 || strcmp(data_in_string,"false") == 0){
        self->type = DTW_COMPLEX_BOOL_TYPE;
        self->value_bool = false;
        free(data);
        return;
    }

    double data_double;
    int result = sscanf(data_in_string,"%lf",&data_double);
    if(result == 0){
        self->type= DTW_COMPLEX_STRING_TYPE;
        self->value_size = value_size;
        self->value_string = data_in_string;
        return;
    }


    for(int i = 0; i < value_size; i++){
        char current = data_in_string[i];
        if(current == '.'){
            free(data);
            self->type = DTW_COMPLEX_DOUBLE_TYPE;
            self->value_double = data_double;
            return;
        }
    }

    free(data);
    self->type = DTW_COMPLEX_LONG_TYPE;
    self->value_long = (long)data_double;

}
 */