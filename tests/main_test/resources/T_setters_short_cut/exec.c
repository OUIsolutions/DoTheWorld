
#include "../../../doTheWorld_test.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/new_folder");
    dtw.resource.set_string_in_sub_resource(values,"nothing","text.txt");

    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png",&size);
    dtw.resource.set_binary_in_sub_resource(values,blob,size,"blob.png");
    free(blob);

    dtw.resource.set_long_in_sub_resource(values,25,"b.txt");
    dtw.resource.set_double_in_sub_resource(values,10.5,"c.txt");
    dtw.resource.set_bool_in_sub_resource(values,true,"b.txt");

    DtwResource  *sub_foder = dtw.resource.sub_resource(values,"sub_foder");
    dtw.resource.set_string_in_sub_resource(sub_foder,"nothing","a.txt");

    dtw.resource.commit(values);
    dtw.resource.free(values);



}





