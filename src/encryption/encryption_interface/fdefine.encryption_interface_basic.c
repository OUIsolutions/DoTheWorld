//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dep_define.h"
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

void DtwEncriptionInterface_free(DtwEncriptionInterface *self){
    self->free_obj(self->obj);
    free(self);
}