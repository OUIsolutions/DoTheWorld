#include "doTheWorldOne.c"

int main() {
    DtwResource *values = new_DtwResource("tests/target/");
    DtwResource *password = DtwResource_sub_resource(values, "password");
    DtwResource_set_string_sha(password, "1234");
    DtwResource_commit(values);
    DtwResource_free(values);
}