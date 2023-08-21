
#include "../../../doTheWorld_test.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/new_folder");

    DtwResource *string_element = dtw.resource.sub_resource_not_loading(values,"text.txt");
    dtw.resource.set_string(string_element,"nothing");
    dtw.resource.free(string_element);
    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png",&size);

    DtwResource *blob_element = dtw.resource.sub_resource_not_loading(values,"blob.png");
    dtw.resource.set_binary(blob_element,blob,size);
    dtw.resource.free(blob_element);
    free(blob);
    DtwResource *bInt = dtw.resource.sub_resource_not_loading(values,"b.txt");
    dtw.resource.set_long(bInt,25);
    dtw.resource.free(bInt);

    DtwResource *cDouble = dtw.resource.sub_resource_not_loading(values,"c.txt");
    dtw.resource.set_double(cDouble,10.5);
    dtw.resource.free(cDouble);

    DtwResource *dBool = dtw.resource.sub_resource_not_loading(values,"b.txt");
    dtw.resource.set_bool(dBool,true);
    dtw.resource.free(dBool);

    DtwResource  *sub_foder = dtw.resource.sub_resource_not_loading(values,"sub_foder");
    DtwResource *string_element2 = dtw.resource.sub_resource_not_loading(sub_foder,"a.txt");
    dtw.resource.set_string(string_element2,"nothing");
    dtw.resource.free(string_element2);

    dtw.resource.free(sub_foder);

    dtw.resource.commit(values);
    dtw.resource.free(values);





}





