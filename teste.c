#include  "src/one.c"


void save_cryto_file(DtwEncriptionInterface *test_interface){
    const char *message = "essa mensagem foi completamente criptografada chupa caraio!!!";
    printf("mensagem original %ld\n",strlen(message));
    DtwEncriptionInterface_write_string_file_content(test_interface,"teste.txt",message);
}
char *load_cryto_file(DtwEncriptionInterface *test_interface){
    return DtwEncriptionInterface_load_string_file_content(test_interface,"teste.txt");
}

int main(){
 
    const char *key  = "teste ";
    const char *iv = "12345678901";
    DtwEncriptionInterface *test_interface = newDtwAES_CBC_EncryptionInterface_str(key,iv);

    save_cryto_file(test_interface);
    char *decrypted = load_cryto_file(test_interface);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    DtwEncriptionInterface_free(test_interface);
    return 0;

}