
#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("testarg");
    dtw.resource.set_string_sha_in_sub_resource(values,"password","1234");
    dtw.resource.commit(values);
    dtw.resource.free(values);





}





