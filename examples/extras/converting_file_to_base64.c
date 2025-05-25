#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    const char *deer_path = "tests/target/blob.png";
    char *deerb64  = dtw_convert_binary_file_to_base64(deer_path);
    printf("blob: %s", deerb64);
    free(deerb64);
}