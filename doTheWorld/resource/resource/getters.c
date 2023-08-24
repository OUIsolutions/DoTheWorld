
unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary){
    private_DtwResource_lock_if_auto_lock(self);
    DtwResource_load_if_not_loaded(self);
    *size = self->value_size;
    *is_binary = self->is_binary;
    return self->value_any;
}

unsigned char *DtwResource_get_binary(DtwResource *self, long *size){
    bool is_binary;
    return DtwResource_get_any(self,size,&is_binary);
}

char *DtwResource_get_string(DtwResource *self){
    long size;
    bool is_binary;
    return (char *)DtwResource_get_any(self,&size,&is_binary);
}

cJSON *DtwResource_get_json(DtwResource *self){
    if(self->value_json){
        return self->value_json;
    }
    char *result = DtwResource_get_string(self);
    self->value_json = cJSON_Parse(result);
    return self->value_json;

}


long DtwResource_get_long(DtwResource *self){
    char *element = DtwResource_get_string(self);
    if(!element){
        return DTW_NOT_FOUND;
    }
    long value;
    int result = sscanf(element,"%ld",&value);
    if(result == 0){
        return DTW_NOT_NUMERICAL;
    }
    return value;
}


double DtwResource_get_double(DtwResource *self){
    char *element = DtwResource_get_string(self);
    if(!element){
        return DTW_NOT_FOUND;
    }
    double value;
    int result = sscanf(element,"%lf",&value);
    if(result == 0){
        return DTW_NOT_NUMERICAL;
    }
    return value;
}

bool DtwResource_get_bool(DtwResource *self){
    char *element = DtwResource_get_string(self);
    if(strcmp(element,"true") == 0 || strcmp(element,"t") == 0){
        return true;
    }
    return false;
}
