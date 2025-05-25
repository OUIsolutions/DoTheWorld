#include "doTheWorldOne.c"

int main() {
    DtwResource *values = new_DtwResource("tests/target/");
    long size;
    unsigned char *content = dtw_load_binary_content("tests/target/blob.png", &size);

    DtwResource_set_binary_sha_in_sub_resource(values, "password", content, size);
    free(content);
    DtwResource_commit(values);
    DtwResource_free(values);

    return 0;
}