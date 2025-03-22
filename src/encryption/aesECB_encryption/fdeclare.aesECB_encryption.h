//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end


void privteDtwAES_ECB_EncryptionInterface_encrypt_buffer(struct AES_ctx *ctx,uint8_t* buf, uint32_t length);

void privteDtwAES_ECB_EncryptionInterface_decrypt_buffer(struct AES_ctx *ctx,uint8_t* buf, uint32_t length);

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface(const uint8_t* key,int key_size);
