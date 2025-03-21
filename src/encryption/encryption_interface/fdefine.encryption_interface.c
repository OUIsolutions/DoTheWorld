//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end


DtwEncriptionInterface *newDtwEncriptionInterface_raw(void *obj,    unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj)){
    DtwEncriptionInterface *self = (DtwEncriptionInterface *)malloc(sizeof(DtwEncriptionInterface));
    self->obj = obj;
    self->encrypt_buffer = encrypt_buffer;
    self->decrypt_buffer = decrypt_buffer;
    self->free_obj = free_obj;
    return self;
}

unsigned char *DtwEncriptionInterface_encrypt_buffer(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size){
    *out_size = 0;
    unsigned char *encrypted = self->encrypt_buffer(self->obj,value,size,out_size);
    encrypted[*out_size] = '\0';
    return encrypted;
}



unsigned char *DtwEncriptionInterface_decrypt_buffer(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary){
    *is_binary = false;
    *out_size = 0;
    unsigned char *content =  self->decrypt_buffer(self->obj,encrypted_value,size,out_size);
    if(content == NULL){
        return NULL;
    }
    content[*out_size] = '\0';
    for(int i= 0; i < *out_size; i++){
        if(content[i] == '\0'){
            *is_binary = true;
            break;
        }    
    }
    return content;

}

bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self, char *file_name,void *value,long size){
    long encrypted_size = 0;
    unsigned char * encrypted = DtwEncriptionInterface_encrypt_buffer(self,(unsigned char *)value,size,&encrypted_size);
    if(encrypted == NULL){
        return false;
    }
    printf("encrypted_size %ld\n",encrypted_size);
    bool result = dtw_write_any_content(file_name,(unsigned char *)encrypted,encrypted_size);
    free(encrypted);
    return result;
}

bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self, char *file_name,const char *value){
    return DtwEncriptionInterface_write_any_content(self,file_name,(void *)value,strlen(value));
}

unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self, char *file_name,long *out_size,bool *is_binary){
    
    long raw_size;
    unsigned char *loaded = dtw_load_binary_content(file_name,&raw_size);
    if(loaded == NULL){
        return NULL;
    }
    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer(self,loaded,raw_size,out_size,is_binary);
    free(loaded);
    return decrypted;
}

char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self, char *file_name){
    bool is_binary;
    long out_size;
    unsigned char *loaded = DtwEncriptionInterface_load_any_content(self,file_name,&out_size,&is_binary);
    printf("out_size %ld\n",out_size);
    if(loaded == NULL){
        return NULL;
    }
    if(is_binary){
        free(loaded);
        return NULL;
    }
    
    return (char *)loaded;
}


void DtwEncriptionInterface_free(DtwEncriptionInterface *self){
    self->free_obj(self->obj);
    free(self);
}