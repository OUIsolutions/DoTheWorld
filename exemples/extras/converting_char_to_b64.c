
#include "../../doTheWorld_test.h"

int main(int argc, char *argv[]){
    long size = 0;
    const char *deer_path = "exemple_folder/deer.jpg";
    unsigned char *content = dtw_load_binary_content(deer_path, &size);
    unsigned char *deerb64 = dtw_base64_encode(content, size);
    printf("deer: %s", deerb64);
    free(deerb64);
    free(content);
}