
#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    long size = 0;
    const char *blob_path = "tests/target/blob.png";
    unsigned char *content = dtw.load_binary_content(blob_path, &size);
    char *blob64 = dtw.base64_encode(content, size);
    printf("blob: %s", blob64);
    free(blob64);
    free(content);
}