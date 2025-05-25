#include "doTheWorldOne.c"


int main(){
    const char *key = "what ever key you want to put with what ever size ";
    DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface(key);
    unsigned char my_message[] = "what ever menssage you want to encrypt";
    long message_size = strlen(my_message);
    const char *b64_encrypted = DtwEncriptionInterface_encrypt_buffer_b64(enc, my_message, message_size);
    if(b64_encrypted == NULL){
        printf("error encrypting\n");
        return 1;
    }
    printf("encrypted %s\n", b64_encrypted);
    
    long decrypted_size = 0;
    bool is_binary = false;
    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer_b64(enc, b64_encrypted, &decrypted_size, &is_binary);
    if(decrypted == NULL){
        printf("error decrypting\n");
        return 1;
    }
    printf("decrypted: %s\n", (char*)decrypted);
    
    free(decrypted);
    free((void*)b64_encrypted);
    DtwEncriptionInterface_free(enc);
    return 0;
}