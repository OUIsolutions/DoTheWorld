//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end


unsigned char * privateDtwAES_ECB_EncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long entry_size,long *out_size){

    privateDtwAES_ECB_EncryptionInterface *self = (privateDtwAES_ECB_EncryptionInterface *)obj;
    long size = entry_size;

    *out_size  =  size + (16 - size % 16);
    unsigned char *result = malloc( *out_size   + 2);
    memcpy(result,value,size);
    bool is16multiple = size % 16 == 0;

        //means the block its complete and we need to add a full extra block filled with 16 bytes
    if(is16multiple){
        printf("$out_size %ld\n",*out_size);        
        memset(result+size,16,16);
    }
    //means the last block is not complete and we need to add the missing bytes
    //the total of empty bytes that we dont sent 
    if(!is16multiple){
        int missing_send_bytes_to_last_block =  *out_size   - size;
        memset(result+size,missing_send_bytes_to_last_block,missing_send_bytes_to_last_block);
    }

    for(int i = 0; i < *out_size; i+=16){
        AES_ECB_encrypt(&self->ctx, ( uint8_t*)result+i);
    }



    return result;
}

unsigned char *privateDtwAES_ECB_EncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long entry_size,long *out_size){
    privateDtwAES_ECB_EncryptionInterface *self = (privateDtwAES_ECB_EncryptionInterface *)obj;
    long size = entry_size;
    
    bool is16multiple = size % 16 == 0;
    if(!is16multiple){
        *out_size = 0;
        
        return NULL;
    }


    
    unsigned char *result = calloc(size + 2,sizeof(unsigned char));
    memcpy(result,encrypted_value,size);
    for(int i = 0; i < size; i+=16){
        AES_ECB_decrypt(&self->ctx, ( uint8_t*)result+i);
    }
    int remaning_bytes = result[size-1];
    *out_size = size - remaning_bytes;
    return result;
}

void  privateDtwAES_ECB_EncryptionInterface_free_obj(void *obj){
    privateDtwAES_ECB_EncryptionInterface *self = (privateDtwAES_ECB_EncryptionInterface *)obj;
    free(self);
}

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface(const uint8_t* key,int key_size){
    privateDtwAES_ECB_EncryptionInterface *self = malloc(sizeof(privateDtwAES_ECB_EncryptionInterface));
    *self = (privateDtwAES_ECB_EncryptionInterface){0};
    memcpy(self->key,key,key_size);
    AES_init_ctx(&self->ctx, key);
    return newDtwEncriptionInterface_raw(self,privateDtwAES_ECB_EncryptionInterface_encrypt_buffer,privateDtwAES_ECB_EncryptionInterface_decrypt_buffer,privateDtwAES_ECB_EncryptionInterface_free_obj);

}
