
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
    int type = dtw_complex_entity_type(self->path);
    
    return dtw_load_long_file_content(self->path);
}


double DtwResource_get_double(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    return  dtw_load_double_file_content(self->path);
}

bool DtwResource_get_bool(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    return  dtw_load_bool_file_content(self->path);
}
