//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end

unsigned char * privateDtwAESECBEncryptionInterface_encrypt_or_decrypt(void *obj,void (*AES_ECB_callback)(struct AES_ctx *ctx, uint8_t* buf), unsigned char *value,long size,long *out_size){
    privateDtwAESECBEncryptionInterface *self = (privateDtwAESECBEncryptionInterface *)obj;
    unsigned char *result = malloc(size+1);
    char buffer[16] = {0};
    for(int i = 0; i < size; i+=16){
        short size_to_copy = 16;
        if(i+16 > size){
            size_to_copy = size - i;
        }
        memcpy(buffer,value+i,size_to_copy);
        AES_ECB_callback(&self->ctx, ( uint8_t*)buffer);
        memcpy(result+i,buffer,size_to_copy);
        memcpy(buffer,"\0",16);
    }
    *out_size = size;
    return result;
}

unsigned char * privateDtwAESECBEncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long size,long *out_size){
    return privateDtwAESECBEncryptionInterface_encrypt_or_decrypt(obj,AES_ECB_encrypt,value,size,out_size);
}

unsigned char *privateDtwAESECBEncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long size,long *out_size){
    return privateDtwAESECBEncryptionInterface_encrypt_or_decrypt(obj,AES_ECB_decrypt,encrypted_value,size,out_size);
}

void  privateDtwAESECBEncryptionInterface_free_obj(void *obj){
    privateDtwAESECBEncryptionInterface *self = (privateDtwAESECBEncryptionInterface *)obj;
    free(self);
}

DtwEncriptionInterface *newDtwAESECBEncryptionInterface(const uint8_t* key,int key_size){
    privateDtwAESECBEncryptionInterface *self = malloc(sizeof(privateDtwAESECBEncryptionInterface));
    *self = (privateDtwAESECBEncryptionInterface){0};
    memcpy(self->key,key,key_size);
    AES_init_ctx(&self->ctx, key);
    return newDtwEncriptionInterface_raw(self,privateDtwAESECBEncryptionInterface_encrypt_buffer,privateDtwAESECBEncryptionInterface_decrypt_buffer,privateDtwAESECBEncryptionInterface_free_obj);

}
