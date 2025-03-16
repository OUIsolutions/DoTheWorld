
#include "doTheWorldOne.c"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/");
    dtw.resource.set_string_sha_in_sub_resource(values,"password","1234");
    dtw.resource.commit(values);
    dtw.resource.free(values);





}
