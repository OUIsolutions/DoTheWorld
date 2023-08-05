
#include "doTheWorld.h"

int main (){

    DtwResource *values = new_DtwResource("tests/target/new_folder");

    DtwResource *string_element = values->sub_resource(values,"text.txt");
    string_element->set_string(string_element,"nothing");
    string_element->free(string_element);
    long size;
    unsigned char *blob = dtw_load_binary_content("tests/target/blob.png",&size);

    DtwResource *blob_element = values->sub_resource(values,"blob.png");
    blob_element->set_binary(blob_element,blob,size);
    blob_element->free(blob_element);
    free(blob);
    DtwResource *bInt = values->sub_resource(values,"b.txt");
    bInt->set_long(bInt,25);
    bInt->free(bInt);

    DtwResource *cDouble = values->sub_resource(values,"c.txt");
    cDouble->set_double(cDouble,10.5);
    cDouble->free(cDouble);

    DtwResource *dBool = values->sub_resource(values,"b.txt");
    dBool->set_bool(dBool,true);
    dBool->free(dBool);

    DtwResource  *sub_foder = values->sub_resource(values,"sub_foder");
    DtwResource *string_element2 = sub_foder->sub_resource(sub_foder,"a.txt");
    string_element2->set_string(string_element2,"nothing");
    string_element2->free(string_element2);

    sub_foder->free(sub_foder);

    values->commit(values);
    values->free(values);





}





