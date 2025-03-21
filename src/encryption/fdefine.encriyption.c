



unsigned char *dtw_encrypt_any_content(unsigned char *value,long size,const char* key){


    struct AES_ctx ctx ={0};
    
    char *sha_of_key = dtw_generate_sha_from_string(key);
    sha_of_key[16] = '\0';
    AES_init_ctx(&ctx, (const uint8_t *)sha_of_key);
   // printf("size %ld\n",size);
    //make size multiple of 16
    long reajusted_size = size + (16 - size % 16);
    ///printf("new size %ld\n",reajusted_size);
    unsigned char *aes_encrypted = (unsigned char *)calloc(reajusted_size+1,sizeof(unsigned char));
    if(aes_encrypted == NULL){
        free(sha_of_key);
        return NULL;
    }
    memcpy(aes_encrypted,value,size);
    AES_CBC_encrypt_buffer(&ctx, aes_encrypted, reajusted_size);
    aes_encrypted[size] = '\0';
    free(sha_of_key);
    return aes_encrypted;
}

unsigned char *dtw_decript_any_content(unsigned char *encriypted,long size,const char* key){
    
    
    char *sha_of_key = dtw_generate_sha_from_string(key);
    sha_of_key[16] = '\0';

    struct AES_ctx ctx ={0};
    AES_init_ctx(&ctx, (const uint8_t *)sha_of_key);


    long reajusted_size = size + (16 - size % 16);
    unsigned char *decrypted = (unsigned char *)calloc(reajusted_size+1,sizeof(unsigned char));
    if(decrypted == NULL){
        free(sha_of_key);
        return NULL;
    }

    memcpy(decrypted,encriypted,size);    
    AES_CBC_decrypt_buffer(&ctx, decrypted, reajusted_size);
    free(sha_of_key);
    return decrypted;
}

unsigned char *dtw_encrypt_string(const char *value,const char* key){
    return dtw_encrypt_any_content((unsigned char*)value,strlen(value),key);
}

char *dtw_decrypt_string(const char *encrypted,const char* key){
    unsigned char *decrypted = dtw_decript_any_content((unsigned char*)encrypted,strlen(encrypted),key);
    if(decrypted == NULL){
        return NULL;
    }
    return (char*)decrypted;
}


bool dtw_write_any_content_encrypting(const char *path,unsigned char *content,long size,const char* key){

    unsigned char *aes_encrypted = dtw_encrypt_any_content(content,size,key);
    if(aes_encrypted == NULL){
        return false;
    }
    bool result = dtw_write_any_content(path,aes_encrypted,size);
    free(aes_encrypted);
    return result;
}
bool dtw_write_string_file_content_encrypting(const char *path,const char *content,const char* key){
    return dtw_write_any_content_encrypting(path,(unsigned char*)content,strlen(content),key);
}


unsigned char *dtw_load_any_content_decrypting(const char * path,const char* key,long *size,bool *is_binary){
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

char *dtw_load_string_file_content_decrypting(const char * path,const char* key){
    long size;
    bool is_binary;
    unsigned char *element = dtw_load_any_content_decrypting(path,key,&size,&is_binary);
    if(element == NULL){
        return NULL;
    }
    if(is_binary){
        free(element);
        return NULL;
    }
    element[size] = '\0';
    return (char*)element;
}