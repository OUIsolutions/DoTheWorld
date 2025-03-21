//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end

typedef struct DtwEncriptionInterface{
    void *obj;
    int   (*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size);
   unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size);
   void (*free_obj)(void *obj);
}DtwEncriptionInterface;


