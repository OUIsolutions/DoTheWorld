#include  "src/one.c"


void save_cryto_file(DtwEncriptionInterface *test_interface){
    const char *message = "mensagem de teste";
    printf("mensagem original %ld\n",strlen(message));
    DtwEncriptionInterface_write_string_file_content(test_interface,"teste.txt",message);
}
char *load_cryto_file(DtwEncriptionInterface *test_interface){
    return DtwEncriptionInterface_load_string_file_content(test_interface,"teste.txt");
}

int main(){
 
    const char *key  = "0123456789012345";
    DtwEncriptionInterface *test_interface = newDtwAES_CBC_EncryptionInterface_str(key,NULL);

    save_cryto_file(test_interface);
    char *decrypted = load_cryto_file(test_interface);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    DtwEncriptionInterface_free(test_interface);


   // printf("b64 %s\n",dtw_convert_binary_file_to_base64("teste.txt"));
    return 0;

}