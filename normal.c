#include  "src/one.c"
#define SIZE 64
int main(){
    const char *key  = "4uncionou essse treco dos inferno4s";
    const char *message = "essa mensagem foi completamente     4";


    dtw_write_string_file_content_encrypting("teste.txt",message,key);

    char *decrypted = dtw_load_string_file_content_decrypting("teste.txt",key);
    printf("Decrypted: %s\n",decrypted);
    free(decrypted);
    return 0;

}