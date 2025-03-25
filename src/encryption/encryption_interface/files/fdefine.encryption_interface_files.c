


bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size){
    long encrypted_size = 0;
    unsigned char * encrypted = DtwEncriptionInterface_encrypt_buffer(self,(unsigned char *)value,size,&encrypted_size);
    if(encrypted == NULL){
        return false;
    }
    bool result = dtw_write_any_content(file_name,(unsigned char *)encrypted,encrypted_size);
    free(encrypted);
    return result;
}


bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self,const char *file_name,const char *value){
    return DtwEncriptionInterface_write_any_content(self,file_name,(unsigned char *)value,strlen(value));
}


unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self,const char *file_name,long *out_size,bool *is_binary){
    
    long raw_size;
    unsigned char *loaded = dtw_load_binary_content(file_name,&raw_size);
    if(loaded == NULL){
        *is_binary = false;
        *out_size = 0;
        return NULL;
    }
    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer(self,loaded,raw_size,out_size,is_binary);
    free(loaded);
    return decrypted;
}




char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self,const char *file_name){
    bool is_binary;
    long out_size;
    unsigned char *loaded = DtwEncriptionInterface_load_any_content(self,file_name,&out_size,&is_binary);
    if(loaded == NULL){
        return NULL;
    }
    if(is_binary){
        free(loaded);
        return NULL;
    }
    
    return (char *)loaded;
}

