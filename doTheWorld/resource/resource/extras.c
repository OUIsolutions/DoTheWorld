




void DtwResource_rename(DtwResource *self, char *new_name){

    char *old_path = strdup(self->path);
    free(self->path);
    self->path  = dtw_concat_path(self->mothhers_path,self->name);

    if(self->allow_transaction){
        DtwTransaction_move_any(self->transaction,old_path,self->path);
    }
    else{
        dtw_move_any(old_path,self->path,DTW_NOT_CONCAT_PATH);
    }
    free(old_path);

}


void DtwResource_lock(DtwResource *self){
    if(self->locked){
        return;
    }
    #ifdef __linux__
        DtwLocker_lock(self->locker,self->path);
    #endif
}
void private_DtwResource_lock_if_auto_lock(DtwResource *self){
    if(self->auto_lock){
        DtwResource_lock(self);
    }
}


void DtwResource_destroy(DtwResource *self){

    if(self->allow_transaction){
        DtwTransaction_delete_any(self->transaction,self->path);
    }
    else{
        dtw_remove_any(self->path);
    }

}






void DtwResource_commit(DtwResource *self){
    DtwTransaction_commit(self->transaction,NULL);
}


int DtwResource_type(DtwResource *self){
    int type_element =  dtw_complex_entity_type(self->path);
    return type_element;
}

DtwStringArray *DtwResource_list(DtwResource *self){
    return dtw_list_all(self->path,DTW_NOT_CONCAT_PATH);
}

const char * DtwResource_type_in_str(DtwResource *self){
     return dtw_convert_entity(DtwResource_type(self));
}

void DtwResource_represent(DtwResource *self){
    printf("path: %s\n", self->path);
    printf("name: %s\n",self->name);
    printf("type: %s\n",DtwResource_type_in_str(self));

}

void DtwResource_clear_cache(DtwResource *self){
    if(!self->cache_state  == DTW_CACHE_UNUSED){
        return;
    }
    

    if(self->cache_type == DTW_COMPLEX_STRING_TYPE || self->cache_type == DTW_COMPLEX_BINARY){
        free(self->cache_any);
    }
    
    self->cache_type = 0;
    self->cache_size = 0;
    self->cache_state = DTW_CACHE_UNUSED;
    self->cache_number = 0;
    self->cache_any = NULL;

}