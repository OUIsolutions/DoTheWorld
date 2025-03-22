#include  "src/one.c"


void save_cryto_file(DtwEncriptionInterface *test_interface){
    const char *message = "essa mensagem foi completamente criptogrvvafada chupa cara!!!";
    printf("mensagem original %ld\n",strlen(message));
    DtwEncriptionInterface_write_string_file_content_b64(test_interface,"teste.txt",message);
}
char *load_cryto_file(DtwEncriptionInterface *test_interface){
    return DtwEncriptionInterface_load_string_file_content_b64(test_interface,"teste.txt");
}

int main(){
 
    const char *key  = "eai parsa agora as chaves são infinitas4";
    DtwEncriptionInterface *test_interface = newDtwAES_Custom_CBC_v1_interface(key);

    save_cryto_file(test_interface);
    char *decrypted = load_cryto_file(test_interface);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    DtwEncriptionInterface_free(test_interface);


   // printf("b64 %s\n",dtw_convert_binary_file_to_base64("teste.txt"));
    return 0;

}