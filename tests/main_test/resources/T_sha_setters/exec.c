
#include "../../../doTheWorld_test.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target/");
    DtwResource *password = dtw.resource.sub_resource(values,"password");
    dtw.resource.set_string_sha(password,"1234");

    dtw.resource.commit(values);
    dtw.resource.free(values);





}





