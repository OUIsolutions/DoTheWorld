



unsigned char *dtw_encrypt_any_content(unsigned char *value,long size,const char* key){
    struct AES_ctx ctx ={0};
    AES_init_ctx(&ctx, (const uint8_t *)key);


    //make size multiple of 16
    size = size + (16 - size % 16);
    
    unsigned char *aes_encrypted = (unsigned char *)calloc(size+1,sizeof(unsigned char));
    if(aes_encrypted == NULL){
        return NULL;
    }
    memcpy(aes_encrypted,value,size);
    AES_CBC_encrypt_buffer(&ctx, aes_encrypted, size);
    return aes_encrypted;
}

unsigned char *dtw_decript_any_content(unsigned char *value,long size,const char* key){
    struct AES_ctx ctx ={0};
    AES_init_ctx(&ctx, (const uint8_t *)key);
    size = size + (16 - size % 16);
    unsigned char *decrypted = (unsigned char *)calloc(size+1,sizeof(unsigned char));
    if(decrypted == NULL){
        return NULL;
    }
    memcpy(decrypted,value,size);    
    AES_CBC_decrypt_buffer(&ctx, decrypted, size);
    return decrypted;
}

unsigned char *dtw_encrypt_string(const char *value,const char* key){
    return dtw_encrypt_any_content((unsigned char*)value,strlen(value),key);
}

char *dtw_decript_string(const char *value,const char* key){
    unsigned char *decrypted = dtw_decript_any_content((unsigned char*)value,strlen(value),key);
    if(decrypted == NULL){
        return NULL;
    }
    return (char*)decrypted;
}


bool dtw_write_encrypted_any_content(const char *path,unsigned char *content,long size,const char* key){

    unsigned char *aes_encrypted = dtw_encrypt_any_content(content,size,key);
    if(aes_encrypted == NULL){
        return false;
    }
    bool result = dtw_write_any_content(path,aes_encrypted,size);
    free(aes_encrypted);
    return result;
}
bool dtw_write_encrypted_string(const char *path,const char *content,const char* key){
    return dtw_write_encrypted_any_content(path,(unsigned char*)content,strlen(content),key);
}


unsigned char *dtw_load_encrypted_content(const char * path,const char* key,long *size,bool *is_binary){
    unsigned char *content = dtw_load_any_content(path,size,is_binary);
    if(content == NULL){
        return NULL;
    }
    unsigned char *decrypted = dtw_decript_any_content(content,*size,key);
    free(content);
    for(int i = 0;i < *size;i++){
        if(decrypted[i] == 0){
            *is_binary = true;
            break;
        }
    }

    return decrypted;
}

char *dtw_load_encrypted_string(const char * path,const char* key){
    long size;
    bool is_binary;
    unsigned char *element = dtw_load_encrypted_content(path,key,&size,&is_binary);
    if(element == NULL){
        return NULL;
    }

    return (char*)element;
}