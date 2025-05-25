#include "doTheWorldOne.c"

int main() {
    DtwResource *values = new_DtwResource("tests/target/");
    DtwResource *password = DtwResource_sub_resource(values, "password");
    long size;
    unsigned char *content = dtw_load_binary_content("tests/target/blob.png", &size);

    DtwResource_set_binary_sha(password, content, size);
    free(content);
    DtwResource_commit(values);
    DtwResource_free(values);
}