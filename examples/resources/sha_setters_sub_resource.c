#include "doTheWorldOne.c"

int main (){
    DtwResource *values = new_DtwResource("tests/target/");
    DtwResource_set_string_sha_in_sub_resource(values,"password","1234");
    DtwResource_commit(values);
    DtwResource_free(values);

}