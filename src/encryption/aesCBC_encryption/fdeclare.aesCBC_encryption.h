//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end


unsigned char * privateDtwAES_CBC_EncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long size,long *out_size);

unsigned char *privateDtwAES_CBC_EncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long size,long *out_size);

void  privateDtwAES_CBC_EncryptionInterface_free_obj(void *obj);

DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface(const uint8_t* key,int key_size);
