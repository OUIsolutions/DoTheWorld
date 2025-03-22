//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end



void privteDtwAES_CBC_EncryptionInterface_encrypt_buffer(struct AES_ctx *ctx,uint8_t* buf, uint32_t length){
    AES_ctx_set_iv(ctx,ctx->iv);
}

void privteDtwAES_CBC_EncryptionInterface_decrypt_buffer(struct AES_ctx *ctx,uint8_t* buf, uint32_t length){
    AES_CBC_decrypt_buffer(ctx, buf, length);
    AES_ctx_set_iv(ctx,ctx->iv);
}

DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface(const uint8_t* key,int key_size,const uint8_t *iv, int iv_size){
    
    if(iv_size == 0){
        return NULL;
    }

    if(iv_size > 16){
        return NULL;
    }


    DtwEncriptionInterface *self = newDtwAES_RAW_EncryptionInterface(key,key_size);
    if(self == NULL){
        return NULL;
    }
    memcpy(self->iv,iv,iv_size);

    self->encrypt_buffer = privteDtwAES_CBC_EncryptionInterface_encrypt_buffer;
    self->decrypt_buffer = privteDtwAES_CBC_EncryptionInterface_decrypt_buffer;
    return self;
}
