

char *DtwEncriptionInterface_encrypt_buffer_b64(DtwEncriptionInterface *self, unsigned char *value,long size){
    long encrypted_size = 0;
    unsigned char * encrypted = DtwEncriptionInterface_encrypt_buffer(self,value,size,&encrypted_size);
    if(encrypted == NULL){
        return NULL;
    }
    char *b64 = dtw_base64_encode(encrypted,encrypted_size);
    free(encrypted);
    return b64;
}

unsigned char *DtwEncriptionInterface_decrypt_buffer_b64(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary){
    
    long b64_out_size;
    unsigned char *decoded = dtw_base64_decode(encrypted_value,&b64_out_size);
    if(decoded == NULL){
        return NULL;
    }
    unsigned char * decrypted =  DtwEncriptionInterface_decrypt_buffer(self,decoded,b64_out_size,out_size,is_binary);
    free(decoded);
    return decrypted;
}


bool DtwEncriptionInterface_write_any_content_b64(DtwEncriptionInterface *self,const char *file_name,unsigned char *value,long size){
    char *b64 = DtwEncriptionInterface_encrypt_buffer_b64(self,(unsigned char *)value,size);
    if(b64 == NULL){
        return false;
    }
    bool result = dtw_write_string_file_content(file_name,b64);
    free(b64);
    return result;
}



bool DtwEncriptionInterface_write_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name,const char *value){
    return DtwEncriptionInterface_write_any_content_b64(self,file_name,(unsigned char *)value,strlen(value));
}



unsigned char *DtwEncriptionInterface_load_any_content_b64(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary){
    char *loaded = dtw_load_string_file_content(file_name);

    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer_b64(self,(const char *)loaded,out_size,is_binary);
    free(loaded);
    return decrypted;
}




char *DtwEncriptionInterface_load_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name){
    long size;
    bool is_binary;
    unsigned char *content = DtwEncriptionInterface_load_any_content_b64(self,file_name,&size,&is_binary);

    if(content == NULL){
        return NULL;
    }
    if(is_binary){
        free(content);
        return NULL;
    }
    return (char*)content;
}

