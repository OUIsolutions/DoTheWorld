

unsigned char * privateDtwAES_RAW_EncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long entry_size,long *out_size){

    privateDtwAES_RAW_EncryptionInterface *self = (privateDtwAES_RAW_EncryptionInterface *)obj;
    long size = entry_size;

    *out_size  =  size + (16 - size % 16);
  
    unsigned char *result = (unsigned char*)malloc( *out_size   + 2);
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

    self->encrypt_buffer(self, ( uint8_t*)result, *out_size);
    return result;
}

unsigned char *privateDtwAES_RAW_EncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long entry_size,long *out_size){
    privateDtwAES_RAW_EncryptionInterface *self = (privateDtwAES_RAW_EncryptionInterface *)obj;
    long size = entry_size;
    
    bool is16multiple = size % 16 == 0;
    if(!is16multiple){
        *out_size = 0;        
        return NULL;
    }
    
    unsigned char *result = (unsigned char *)calloc(size + 2,sizeof(unsigned char));
    memcpy(result,encrypted_value,size);
    self->decrypt_buffer(self, ( uint8_t*)result,size);
    int remaning_bytes = result[size-1];
    *out_size = size - remaning_bytes;
    return result;
}

void  privateDtwAES_RAW_EncryptionInterface_free_obj(void *obj){
    privateDtwAES_RAW_EncryptionInterface *self = (privateDtwAES_RAW_EncryptionInterface *)obj;
    free(self);
}


DtwEncriptionInterface *newDtwAES_RAW_EncryptionInterface(const uint8_t* key,int key_size){
   
    if(key_size == 0){
        return NULL;
    }
    if(key_size > 16){
        return NULL;
    }
    privateDtwAES_RAW_EncryptionInterface *self = (privateDtwAES_RAW_EncryptionInterface *)malloc(sizeof(privateDtwAES_RAW_EncryptionInterface));
    *self = (privateDtwAES_RAW_EncryptionInterface){0};
    memcpy(self->key,key,key_size);

    return newDtwEncriptionInterface_raw(self,privateDtwAES_RAW_EncryptionInterface_encrypt_buffer,privateDtwAES_RAW_EncryptionInterface_decrypt_buffer,privateDtwAES_RAW_EncryptionInterface_free_obj);
}
