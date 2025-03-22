

void privteDtwAES_ECB_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

void privteDtwAES_ECB_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface(const uint8_t* key,int key_size);

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface_str(const char* key);
