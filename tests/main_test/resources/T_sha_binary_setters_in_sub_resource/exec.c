
#include "../../../../release/doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/");
    long size;
    unsigned   char *content = dtw_load_binary_content("tests/target/blob.png",&size);

    dtw.resource.set_binary_sha_in_sub_resource(values,"password",content,size);
    free(content);
    dtw.resource.commit(values);
    dtw.resource.free(values);





}
