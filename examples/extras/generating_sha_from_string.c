#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    const char *test = "Hello World!";
    char *hash = dtw_generate_sha_from_string(test);  // Replaced namespace call with direct function
    printf("SHA: %s", hash);
    free(hash);
}