#include  "src/one.c"

int main(){
    const char *key  ="eai parsa suave";
    const char *message = "essamensagem foi completamente encriptada";
    dtw_write_aes_encrypted_string("teste.txt",message, key);
    char *decrypted = dtw_load_aes_encrypted_string("teste.txt", key);
    printf("Decrypted: %s\n", decrypted);
    free(decrypted);
}