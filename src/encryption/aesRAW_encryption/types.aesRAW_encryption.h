//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end



typedef struct privateDtwAES_RAW_EncryptionInterface{
     uint8_t key[16];
     struct AES_ctx  ctx;
     uint8_t temp_iv[16];
     uint8_t iv[16];
     void (*encrypt_buffer)(struct AES_ctx *ctx,uint8_t* buf, uint32_t length);
     void (*decrypt_buffer)(struct AES_ctx *ctx,uint8_t* buf, uint32_t length);

}privateDtwAES_RAW_EncryptionInterface;