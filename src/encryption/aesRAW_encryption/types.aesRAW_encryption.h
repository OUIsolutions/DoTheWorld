//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end



typedef struct privateDtwAES_RAW_EncryptionInterface{
     uint8_t key[16];
     struct AES_ctx  ctx;
     uint8_t iv[16];
     void (*encrypt_buffer)( struct privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);
     void (*decrypt_buffer)(struct privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

}privateDtwAES_RAW_EncryptionInterface;