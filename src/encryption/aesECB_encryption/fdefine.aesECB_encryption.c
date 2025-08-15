//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end

void privteDtwAES_ECB_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length){
    
    for(int i = 0; i < length; i+=16){
        AES_ECB_encrypt(&self->ctx, buf+i);
    }
}

void privteDtwAES_ECB_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length){
    for(int i = 0; i < length; i+=16){
        AES_ECB_decrypt(&self->ctx, buf+i);
    }
}

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface(const uint8_t* key,int key_size){
    DtwEncriptionInterface *obj = newDtwAES_RAW_EncryptionInterface(key,key_size);
    if(obj == NULL){
        return NULL;
    }
    
   privateDtwAES_RAW_EncryptionInterface *self = (privateDtwAES_RAW_EncryptionInterface *)obj->obj;
    AES_init_ctx(&self->ctx,key);
   self->encrypt_buffer = privteDtwAES_ECB_EncryptionInterface_encrypt_buffer;
   self->decrypt_buffer = privteDtwAES_ECB_EncryptionInterface_decrypt_buffer;
   return obj;
}

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface_str(const char* key){
    return newDtwAES_ECB_EncryptionInterface((uint8_t*)key,strlen(key));
}