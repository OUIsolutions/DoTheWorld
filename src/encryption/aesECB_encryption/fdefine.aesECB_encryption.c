//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end


unsigned char * privateDtwAESECBEncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long size,long *out_size){

    privateDtwAESECBEncryptionInterface *self = (privateDtwAESECBEncryptionInterface *)obj;

    long content_out_size =  size + (16 - size % 16);
    unsigned char *result = malloc(content_out_size + 2);
    memcpy(result,value,size);
    for(int i = 0; i < size; i+=16){
        AES_ECB_encrypt(&self->ctx, ( uint8_t*)result+i);
    }

    printf("size %ld\n",size);
    printf("content_out_size %ld\n",content_out_size);


    //means the block its complete and we need to add a full extra block filled with 16 bytes
    if(size == content_out_size){
        *out_size = size + 16;
        memset(result+size,16,16);
    }
    //means the last block is not complete and we need to add the missing bytes
    //the total of empty bytes that we dont sent 
    if(size < content_out_size){
        *out_size = size;
        int missing_send_bytes_to_last_block = content_out_size - size;
        memset(result+size,missing_send_bytes_to_last_block,missing_send_bytes_to_last_block);
    }

  


    return result;
}

unsigned char *privateDtwAESECBEncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long size,long *out_size){
    privateDtwAESECBEncryptionInterface *self = (privateDtwAESECBEncryptionInterface *)obj;
    unsigned char *result = malloc(size + 2);
    for(int i = 0; i < size; i+=16){
        AES_ECB_decrypt(&self->ctx, ( uint8_t*)result+i);
    }
    *out_size = size;
    return result;
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
