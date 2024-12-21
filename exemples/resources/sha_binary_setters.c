
#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("testarg");
    DtwResource *password = dtw.resource.sub_resource(values,"password");
    long size;
    unsigned   char *content = dtw_load_binary_content("testargblob.png",&size);

    dtw.resource.set_binary_sha(password,content,size);
    free(content);
    dtw.resource.commit(values);
    dtw.resource.free(values);





}





