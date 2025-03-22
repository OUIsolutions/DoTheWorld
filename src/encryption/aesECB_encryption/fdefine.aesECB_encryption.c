//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end

void privteDtwAES_ECB_EncryptionInterface_encrypt_buffer(struct AES_ctx *ctx,uint8_t* buf, uint32_t length){
    
    for(int i = 0; i < length; i+=16){
        AES_ECB_encrypt(ctx, buf+i);
    }
}

void privteDtwAES_ECB_EncryptionInterface_decrypt_buffer(struct AES_ctx *ctx,uint8_t* buf, uint32_t length){
    for(int i = 0; i < length; i+=16){
        AES_ECB_decrypt(ctx, buf+i);
    }
}

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface(const uint8_t* key,int key_size){
    DtwEncriptionInterface *self = newDtwAES_RAW_EncryptionInterface(key,key_size);
    if(self == NULL){
        return NULL;
    }
   self->encrypt_buffer = privteDtwAES_ECB_EncryptionInterface_encrypt_buffer;
   self->decrypt_buffer = privteDtwAES_ECB_EncryptionInterface_decrypt_buffer;
   return self;
}
