


DtwEncriptionInterface *newDtwAES_Custom_CBC_v1_interface(const char *key){
    if(key == NULL){
        return NULL;
    }
    char *sha1 = dtw_generate_sha_from_string(key);
    char *sha2 = dtw_generate_sha_from_string(sha1);
    DtwEncriptionInterface *self = newDtwAES_CBC_EncryptionInterface((uint8_t*)sha1,16,(uint8_t*)sha2,16);
    free(sha1);
    free(sha2);
    return self;

}
