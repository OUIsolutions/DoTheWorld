
#include  "doTheWorldOne.c"


DtwNamespace dtw;

int main(){
    dtw = newDtwNamespace();
    const char *key ="what ever key you want to put with what ever size ";//can be any size
    DtwEncriptionInterface *enc = dtw.encryption.newAES_Custom_CBC_v1_interface(key);
    unsigned char my_messsage[] = "what ever menssage you want to encrypt";
    long message_size = strlen(my_messsage);
    const char *b64_encrypted = dtw.encryption.encrypt_buffer_b64(enc,my_messsage,message_size);
    if(b64_encrypted == NULL){
        printf("error encrypting\n");
        return 1;
    }
    printf("encrypted %s\n",b64_encrypted);
    
    long dectypted_size = 0;
    bool is_binary = false;
    unsigned char *decrypted = dtw.encryption.decrypt_buffer_b64(enc,b64_encrypted,&dectypted_size,&is_binary);
    if(decrypted == NULL){
        printf("error decrypting\n");
        return 1;
    }
    printf("decrypted: %s\n",(char*)decrypted);
    
    free(decrypted);
    free((void*)b64_encrypted);
    dtw.encryption.free(enc);
    return 0;

}