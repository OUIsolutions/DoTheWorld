#include  "src/one.c"


void save_cryto_file(DtwEncriptionInterface *test_interface){
    const char *message = "mensagem de teste";
    printf("mensagem original %ld\n",strlen(message));
    DtwEncriptionInterface_write_string_file_content_b64(test_interface,"teste.txt",message);
}
char *load_cryto_file(DtwEncriptionInterface *test_interface){
    return DtwEncriptionInterface_load_string_file_content_b64(test_interface,"teste.txt");
}

int main(){
 
    const char *key  = "teste";
    DtwEncriptionInterface *test_interface = newDtwAES_ECB_EncryptionInterface_str(key);

    save_cryto_file(test_interface);
    char *decrypted = load_cryto_file(test_interface);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    DtwEncriptionInterface_free(test_interface);


   // printf("b64 %s\n",dtw_convert_binary_file_to_base64("teste.txt"));
    return 0;

}