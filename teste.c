#include  "src/one.c"


void save_cryto_file(DtwEncriptionInterface *interface){
    const char *message = "essa mensagem foi completamente criptografada chupa caraio!!!";
    printf("mensagem original %ld\n",strlen(message));
    DtwEncriptionInterface_write_string_file_content(interface,"teste.txt",message);
}
char *load_cryto_file(DtwEncriptionInterface *interface){
    return DtwEncriptionInterface_load_string_file_content(interface,"teste.txt");
}

int main(){
 
    const char *key  = "teste ";
    const char *iv = "12345678901";
    DtwEncriptionInterface *interface = newDtwAES_CBC_EncryptionInterface_str(key,iv);

    save_cryto_file(interface);
    char *decrypted = load_cryto_file(interface);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    DtwEncriptionInterface_free(interface);
    return 0;

}