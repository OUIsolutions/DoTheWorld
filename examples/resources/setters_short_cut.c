#include "doTheWorldOne.c"

int main (){
    DtwResource *values = new_DtwResource("tests/target/new_folder");
    DtwResource_set_string_in_sub_resource(values,"text.txt","nothing");

    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png",&size);
    DtwResource_set_binary_in_sub_resource(values,"blob.png",blob,size);
    free(blob);

    DtwResource_set_long_in_sub_resource(values,"b.txt",25);
    DtwResource_set_double_in_sub_resource(values,"c.txt",10.5);
    DtwResource_set_bool_in_sub_resource(values,"b.txt",true);

    DtwResource *sub_foder = DtwResource_sub_resource(values,"sub_foder");
    DtwResource_set_string_in_sub_resource(sub_foder,"a.txt","nothing");

    DtwResource_commit(values);
    DtwResource_free(values);
    DtwResource_free(sub_foder);
}
