
unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);

    unsigned char *result = dtw_load_any_content(path,size,is_binary);
    free(path);
    return result;
}

unsigned char *DtwResource_get_binary(DtwResource *self, long *size){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    unsigned  char *result = dtw_load_binary_content(path,size);
    free(path);
    return result;
}

char *DtwResource_get_string(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    char *result = dtw_load_string_file_content(path);
    free(path);
    return result;
}

long DtwResource_get_long(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    long result =  dtw_load_long_file_content(path);
    free(path);
    return result;
}


double DtwResource_get_double(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    double result =  dtw_load_double_file_content(path);
    free(path);
    return result;
}

bool DtwResource_get_bool(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    bool result = dtw_load_bool_file_content(path);
    free(path);
    return result;
}
