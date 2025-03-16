
#include "doTheWorldOne.c"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/new_folder");

    DtwResource *string_element = dtw.resource.sub_resource(values,"text.txt");
    dtw.resource.set_string(string_element,"nothing");
    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png",&size);

    DtwResource *blob_element = dtw.resource.sub_resource(values,"blob.png");
    dtw.resource.set_binary(blob_element,blob,size);

    free(blob);
    DtwResource *bInt = dtw.resource.sub_resource(values,"b.txt");
    dtw.resource.set_long(bInt,25);

    DtwResource *cDouble = dtw.resource.sub_resource(values,"c.txt");
    dtw.resource.set_double(cDouble,10.5);

    DtwResource *dBool = dtw.resource.sub_resource(values,"b.txt");
    dtw.resource.set_bool(dBool,true);

    DtwResource  *sub_foder = dtw.resource.sub_resource(values,"sub_foder");
    DtwResource *string_element2 = dtw.resource.sub_resource(sub_foder,"a.txt");
    dtw.resource.set_string(string_element2,"nothing");


    dtw.resource.commit(values);
    dtw.resource.free(values);





}
