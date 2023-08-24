#include "../../../doTheWorld_test.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target");

    DtwResourceArray *listage = dtw.resource.sub_resources(values);
    for(int i = 0; i < listage->size;i++){
        DtwResource * current = listage->resources[i];
        dtw.resource.represent(current);
    }

    dtw.resource.free(values);



}




