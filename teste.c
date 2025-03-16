#include "src/one.c"

int main(){
    char *converted = dtw_base64_encode("Hello World", 11);
    printf("Encoded: %s\n", converted);
    free(converted);
}