#include  "src/one.c"


void save_cryto_file(DtwEncriptionInterface *test_interface){
    const char *message = "teste";
    printf("mensagem original %ld\n",strlen(message));
    DtwEncriptionInterface_write_string_file_content(test_interface,"teste.txt",message);
}
char *load_cryto_file(DtwEncriptionInterface *test_interface){
    return DtwEncriptionInterface_load_string_file_content(test_interface,"teste.txt");
}

int main(){

    char *result = dtw_convert_binary_to_hex((unsigned char *)"eai parsa suave",strlen("eai parsa suave"));
    printf("Hex: %s\n",result);

    long size;
    unsigned char *binary = dtw_convert_hex_to_binary(result, &size);
    printf("Binary: %s\n",binary);
    free(binary);
    free(result);

    return 0;
    const char *key  = "0123456789012345";
    DtwEncriptionInterface *test_interface = newDtwAES_CBC_EncryptionInterface_str(key,key);

    save_cryto_file(test_interface);
    char *decrypted = load_cryto_file(test_interface);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    DtwEncriptionInterface_free(test_interface);


   // printf("b64 %s\n",dtw_convert_binary_file_to_base64("teste.txt"));
    return 0;

}