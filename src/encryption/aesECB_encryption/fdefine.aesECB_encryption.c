//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end


unsigned char * privateDtwAESECBEncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long size,long *out_size){

    privateDtwAESECBEncryptionInterface *self = (privateDtwAESECBEncryptionInterface *)obj;

    long content_out_size =  size + (16 - size % 16);
    int extra_bytes = content_out_size - size;

    printf("size %ld\n",size);
    printf("content_out_size %ld\n",content_out_size);
    printf("extra_bytes %d\n",extra_bytes);

    unsigned char *result = malloc(content_out_size + 2);

    if(extra_bytes == 0){
        //since block size is 16, we need to add a block with padding
        *out_size = content_out_size+1;
        result[content_out_size] = 16;      
    }

    if(extra_bytes > 0){
        *out_size = content_out_size;
        memset(result+size,extra_bytes,extra_bytes);
    }
  
    memcpy(result,value,size);
    for(int i = 0; i < size; i+=16){
        AES_ECB_encrypt(&self->ctx, ( uint8_t*)result+i);
    }

    return result;
}

unsigned char *privateDtwAESECBEncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long size,long *out_size){
  
  bool is_16_multiple = size % 16 == 0;
  if(!is_16_multiple){
    //if multiple of16 means not all bytes were sent into the last block
     *out_size = size-1;
  }

  if(is_16_multiple){
    //if multiple of16 means not all bytes were sent into the last block
    int extra_bytes = encrypted_value[size-1];
    *out_size = size - extra_bytes;
  }

    return NULL;
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
