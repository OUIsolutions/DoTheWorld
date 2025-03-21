



unsigned char *dtw_aes_encrypt_any_content(unsigned char *value,long size,const char* key){
    struct AES_ctx ctx ={0};
    AES_init_ctx(&ctx, (const uint8_t *)key);
    
    unsigned char *encrypted = (unsigned char *)malloc(size+1);
    if(encrypted == NULL){
        return NULL;
    }
    memcpy(encrypted,value,size);
    encrypted[size] = '\0';
    AES_ECB_encrypt(&ctx, encrypted);
    return encrypted;
}

unsigned char *dtw_aes_decript_any_content(unsigned char *value,long size,const char* key){
    struct AES_ctx ctx ={0};
    AES_init_ctx(&ctx, (const uint8_t *)key);
    
    unsigned char *decrypted = (unsigned char *)malloc(size+1);
    if(decrypted == NULL){
        return NULL;
    }
    memcpy(decrypted,value,size);
    decrypted[size] = '\0';
    AES_ECB_decrypt(&ctx, decrypted);
    return decrypted;
}

unsigned char *dtw_aes_encrypt_string(const char *value,const char* key){
    return dtw_aes_encrypt_any_content((unsigned char*)value,strlen(value),key);
}

char *dtw_aes_decript_string(const char *value,const char* key){
    unsigned char *decrypted = dtw_aes_decript_any_content((unsigned char*)value,strlen(value),key);
    if(decrypted == NULL){
        return NULL;
    }
    return (char*)decrypted;
}


bool dtw_write_encrypted_any_content(const char *path,unsigned char *content,long size,const char* key){

    unsigned char *encrypted = dtw_aes_encrypt_any_content(content,size,key);
    if(encrypted == NULL){
        return false;
    }
    bool result = dtw_write_any_content(path,encrypted,size);
    free(encrypted);
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
    unsigned char *decrypted = dtw_aes_decript_any_content(content,*size,key);
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
    if(is_binary){
        free(element);
        return NULL;
    }
    return (char*)element;
}