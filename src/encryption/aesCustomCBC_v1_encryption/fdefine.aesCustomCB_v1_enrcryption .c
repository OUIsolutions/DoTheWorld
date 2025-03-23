


DtwEncriptionInterface *newDtwAES_Custom_CBC_v1_interface(const char *key){
    if(key == NULL){
        return NULL;
    }
    DtwHash *hash = newDtwHash();
    DtwHash_digest_string(hash,"isiojerjwj92392-10i4i5i3954ii2323-2");
    DtwHash_digest_string(hash,key);
    char *sha1 = strdup(hash->hash);
    DtwHash_digest_string(hash,"is439i023203bjgffgfokk,fiwjj2342124432");
    char *sha2 = strdup(hash->hash);
    DtwEncriptionInterface *self = newDtwAES_CBC_EncryptionInterface((uint8_t*)sha1,16,(uint8_t*)sha2,16);
    free(sha1);
    free(sha2);
    DtwHash_free(hash);
    return self;

}
