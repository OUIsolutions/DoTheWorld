
unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary){
    private_DtwResource_lock_if_auto_lock(self);

    return dtw_load_any_content(self->path,size,is_binary);
}

unsigned char *DtwResource_get_binary(DtwResource *self, long *size){
    private_DtwResource_lock_if_auto_lock(self);
    return dtw_load_binary_content(self->path,size);
}


char *DtwResource_get_string(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    
    if(self->cache_state == DTW_CACHE_LOADED && !self->resset_cache && self->cache_type == DTW_COMPLEX_STRING_TYPE){
        return (char*)self->cache_any;
    }

    DtwResource_clear_cache(self);
    
    char *result = dtw_load_string_file_content(self->path);

    if(result){
        self->cache_state  = DTW_CACHE_LOADED;
        self->cache_type = DTW_COMPLEX_STRING_TYPE;
        self->cache_any = (unsigned char *)result;
        self->cache_size = strlen(result);
    }
    return result;

}

long DtwResource_get_long(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);

    if(
        self->cache_state == DTW_CACHE_LOADED 
        && !self->resset_cache 
        && (    self->cache_type == DTW_COMPLEX_LONG_TYPE 
                ||self->cache_type == DTW_COMPLEX_DOUBLE_TYPE 
           )
        ){
         return (long)self->cache_number;
    }

    DtwResource_clear_cache(self);
    int error =  0;
    long result = dtw_load_long_file_content_setting_error(self->path,&error);
    if(error == 0){
        self->cache_state = DTW_CACHE_LOADED;
        self->cache_type = DTW_COMPLEX_LONG_TYPE;
        self->cache_number = (double)result;
    }
    return  result;
}


double DtwResource_get_double(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);

    if(
        self->cache_state == DTW_CACHE_LOADED 
        && !self->resset_cache 
        && self->cache_type == DTW_COMPLEX_DOUBLE_TYPE 
           
        ){
         return self->cache_number;
    }
    DtwResource_clear_cache(self);
    int error =  0;
    double result = dtw_load_double_file_content_setting_error(self->path,&error);
    if(error == 0){
        self->cache_state = DTW_CACHE_LOADED;
        self->cache_type = DTW_COMPLEX_DOUBLE_TYPE;
        self->cache_number = result;
    }
    return  result;
}



bool DtwResource_get_bool(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    return  dtw_load_bool_file_content(self->path);
}
