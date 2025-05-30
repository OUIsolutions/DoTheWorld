#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    const char *path = "tests/target/blob.png";
    long size;
    bool is_binary;
    // Load any file, useful if you don\'t know if the file is binary or not
    unsigned char *content = dtw_load_any_content(path, &size, &is_binary);
    if (content == NULL) {
        printf("error opening %s\n", path);
        return 1;
    }
    printf("size: %ld\n", size);
    printf("is_binary: %s\n", is_binary ? "true" : "false");

    dtw_write_any_content("tests/target/blob2.png", content, size);
    free(content);
    return 0;
}