#include  "src/one.c"
#define SIZE 64
int main(){
     char key[16]  = "essachave123456";
    const char *message = "essa mensagem foi completamente encriptada";
    
    struct AES_ctx ctx = {0};
    AES_init_ctx(&ctx, (const uint8_t*)key);


    unsigned char encriped[1000] = {0};
    memcpy(encriped,message,strlen(message));

    AES_CBC_encrypt_buffer(&ctx,encriped,SIZE);
    printf("Encripted:");
    for(int i = 0;i < strlen(message);i++){
        printf(" %d ",encriped[i]);
    }
    printf("\n");



    struct AES_ctx ctx2 = {0};
    AES_init_ctx(&ctx2, (const uint8_t*)key);

    unsigned char decripted[1000] = {0};
    memcpy(decripted,encriped,SIZE);
    AES_CBC_decrypt_buffer(&ctx2,decripted,SIZE);
    decripted[SIZE] = '\0';
    
    printf("Decripted:");
    for(int i = 0;i < strlen(message);i++){
        printf("%c",decripted[i]);
    }


    printf("\n");
    return 0;

}