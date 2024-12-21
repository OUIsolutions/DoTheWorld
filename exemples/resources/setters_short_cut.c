
#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("testargnew_folder");
    dtw.resource.set_string_in_sub_resource(values,"text.txt","nothing");

    long size;
    unsigned char *blob = dtw_load_binary_content("testargblob.png",&size);
    dtw.resource.set_binary_in_sub_resource(values,"blob.png",blob,size);
    free(blob);

    dtw.resource.set_long_in_sub_resource(values,"b.txt",25);
    dtw.resource.set_double_in_sub_resource(values,"c.txt",10.5);
    dtw.resource.set_bool_in_sub_resource(values,"b.txt",true);

    DtwResource  *sub_foder = dtw.resource.sub_resource(values,"sub_foder");
    dtw.resource.set_string_in_sub_resource(sub_foder,"a.txt","nothing");

    dtw.resource.commit(values);
    dtw.resource.free(values);



}





