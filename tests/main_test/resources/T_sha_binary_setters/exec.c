
#include "../../../../release/doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/");
    DtwResource *password = dtw.resource.sub_resource(values,"password");
    long size;
    unsigned   char *content = dtw_load_binary_content("tests/target/blob.png",&size);

    dtw.resource.set_binary_sha(password,content,size);
    free(content);
    dtw.resource.commit(values);
    dtw.resource.free(values);





}
