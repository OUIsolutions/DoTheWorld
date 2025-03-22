#include  "doTheWorldOne.c"


DtwNamespace dtw;

int main(){
    dtw = newDtwNamespace();
    const char *key  = "my custom key";// needs to be lower then 16 
    int key_size = strlen(key);
    if(key_size > 16){
        printf("key size must be lower then 16\n");
        return 1;
    }
    DtwEncriptionInterface *enc = dtw.encryption.newAES_ECB_EncryptionInterface_str(key);
    unsigned char my_messsage[] = "what ever menssage you want to encrypt";
    long message_size = strlen(my_messsage);
    const char *hex_encrypted = dtw.encryption.encrypt_buffer_hex(enc,my_messsage,message_size);
    if(hex_encrypted == NULL){
        printf("error encrypting\n");
        return 1;
    }
    printf("encrypted %s\n",hex_encrypted);
    
    long dectypted_size = 0;
    bool is_binary = false;
    unsigned char *decrypted = dtw.encryption.decrypt_buffer_hex(enc,hex_encrypted,&dectypted_size,&is_binary);
    if(decrypted == NULL){
        printf("error decrypting\n");
        return 1;
    }
    printf("decrypted: %s\n",(char*)decrypted);
    
    free(decrypted);
    free((void*)hex_encrypted);
    dtw.encryption.free(enc);
    return 0;

}