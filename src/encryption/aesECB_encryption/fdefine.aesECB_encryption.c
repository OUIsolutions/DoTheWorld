//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end

unsigned char * privateDtwAESECBEncryptionInterface_encrypt_or_decrypt(void *obj,void (*AES_ECB_callback)(struct AES_ctx *ctx, uint8_t* buf), unsigned char *value,long size){
    privateDtwAESECBEncryptionInterface *self = (privateDtwAESECBEncryptionInterface *)obj;

    unsigned char *result = malloc(size + 20);
    memcpy(result,value,size);

    for(int i = 0; i < size; i+=16){
        AES_ECB_callback(&self->ctx, ( uint8_t*)result+i);
    }

    return result;
}

unsigned char * privateDtwAESECBEncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long size,long *out_size){
    
    unsigned char *content = privateDtwAESECBEncryptionInterface_encrypt_or_decrypt(obj,AES_ECB_encrypt,value,size);
    //these its the padding control
    long content_out_size =  size + (16 - size % 16);
    int remaining = content_out_size - size;
    content[content_out_size] = remaining;
    *out_size = content_out_size+1;
    return content;
}

unsigned char *privateDtwAESECBEncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long size,long *out_size){
    
    //get the remaining
    int remaining = encrypted_value[size-1];
    long encrypted_size = size -1;
    *out_size = encrypted_size - remaining;
    return privateDtwAESECBEncryptionInterface_encrypt_or_decrypt(obj,AES_ECB_decrypt,encrypted_value,encrypted_size);
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
