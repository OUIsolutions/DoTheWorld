#include "doTheWorldOne.c"

int main() {
    DtwNamespace dtw = newDtwNamespace();  // Keep this as it's the entry point for the namespace

    DtwResource *values = new_DtwResource("tests/target/new_folder");

    DtwResource *string_element = DtwResource_sub_resource(values, "text.txt");
    DtwResource_set_string(string_element, "nothing");
    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png", &size);

    DtwResource *blob_element = DtwResource_sub_resource(values, "blob.png");
    DtwResource_set_binary(blob_element, blob, size);

    free(blob);
    DtwResource *bInt = DtwResource_sub_resource(values, "b.txt");
    DtwResource_set_long(bInt, 25);

    DtwResource *cDouble = DtwResource_sub_resource(values, "c.txt");
    DtwResource_set_double(cDouble, 10.5);

    DtwResource *dBool = DtwResource_sub_resource(values, "b.txt");
    DtwResource_set_bool(dBool, true);

    DtwResource *sub_foder = DtwResource_sub_resource(values, "sub_foder");
    DtwResource *string_element2 = DtwResource_sub_resource(sub_foder, "a.txt");
    DtwResource_set_string(string_element2, "nothing");

    DtwResource_commit(values);
    DtwResource_free(values);

    return 0;  // Ensure the function ends properly
}