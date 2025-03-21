#include  "src/one.c"
#define SIZE 64


void save_cryto_file(DtwEncriptionInterface *interface){
    const char *message = "essa mensagem foi completamente encriptada12345678";
    printf("mensagem original %ld\n",strlen(message));
    long size = 0;
    bool is_binary = false;
    printf("size de escrita %ld\n",size);
    unsigned char *encrypted = DtwEncriptionInterface_encrypt_buffer(interface,(unsigned char *)message,strlen(message),&size);
    printf("--------------------------------------\n");
    dtw_write_any_content("teste.txt",encrypted,size);
    free(encrypted);  
}
char *load_cryto_file(DtwEncriptionInterface *interface){
    long size = 0;
    bool is_binary = false;
    unsigned char *encrypted = dtw_load_binary_content("teste.txt",&size);
    printf("size de leitura %ld\n",size);

    char *decrypted = DtwEncriptionInterface_decrypt_buffer(interface,encrypted,size,&size,&is_binary);
    free(encrypted);
    return decrypted;
}
int main(){
    const char *key  = "teste ";

    
    DtwEncriptionInterface *interface = newDtwAESECBEncryptionInterface(key,strlen(key));
    DtwEncriptionInterface *interface2 = newDtwAESECBEncryptionInterface(key,strlen(key));

    save_cryto_file(interface);
    char *decrypted = load_cryto_file(interface2);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    DtwEncriptionInterface_free(interface2);
    DtwEncriptionInterface_free(interface);
    return 0;

}