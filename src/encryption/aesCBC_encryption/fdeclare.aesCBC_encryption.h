

void privteDtwAES_CBC_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);


void privteDtwAES_CBC_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);
DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface(const uint8_t* key,int key_size,const uint8_t *iv, int iv_size);

DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface_str(const char* key,const char *iv);
