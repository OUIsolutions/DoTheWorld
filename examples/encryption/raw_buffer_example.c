#include "doTheWorldOne.c"

int main(){
    const char *key ="what ever key you want to put with what ever size ";//can be any size
    DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface(key);
    unsigned char my_messsage[] = "what ever menssage you want to encrypt";
    long message_size = strlen(my_messsage);
    long encryted_size = 0;
    unsigned char *encrypted = DtwEncriptionInterface_encrypt_buffer(enc,my_messsage,message_size,&encryted_size);
    if(encrypted == NULL){
        printf("error encrypting\n");
        return 1;
    }
    printf("encrypted:");
    for(long i = 0; i < encryted_size; i++){
        printf("%d ",encrypted[i]);
    }
    printf("\n");
    
    long dectypted_size = 0;
    bool is_binary = false;
    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer(enc,encrypted,encryted_size,&dectypted_size,&is_binary);
    if(decrypted == NULL){
        printf("error decrypting\n");
        return 1;
    }
    printf("decrypted: %s\n",(char*)decrypted);
    printf("\n");
    free(decrypted);
    free((void*)encrypted);
    DtwEncriptionInterface_free(enc);
    return 0;

}