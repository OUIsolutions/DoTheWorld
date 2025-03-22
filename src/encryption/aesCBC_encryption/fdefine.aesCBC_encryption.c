


void privteDtwAES_CBC_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length){
    AES_CBC_encrypt_buffer(&self->ctx, buf, length);
    AES_ctx_set_iv(&self->ctx,self->iv);
}

void privteDtwAES_CBC_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length){
    AES_CBC_decrypt_buffer(&self->ctx, buf, length);
    AES_ctx_set_iv(&self->ctx,self->iv);
}

DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface(const uint8_t* key,int key_size,const uint8_t *iv, int iv_size){
    
    if(iv_size == 0){
        return NULL;
    }

    if(iv_size > 16){
        return NULL;
    }


    DtwEncriptionInterface *obj = newDtwAES_RAW_EncryptionInterface(key,key_size);
    if(obj == NULL){
        return NULL;
    }

    privateDtwAES_RAW_EncryptionInterface *self = (privateDtwAES_RAW_EncryptionInterface *)obj->obj;
    memcpy(self->iv,iv,iv_size);
    AES_init_ctx_iv(&self->ctx,self->key,self->iv); 

    self->encrypt_buffer = privteDtwAES_CBC_EncryptionInterface_encrypt_buffer;
    self->decrypt_buffer = privteDtwAES_CBC_EncryptionInterface_decrypt_buffer;
    return obj;
}
DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface_str(const char* key,const char *iv){
    return newDtwAES_CBC_EncryptionInterface((uint8_t*)key,strlen(key),(uint8_t*)iv,strlen(iv));
}
