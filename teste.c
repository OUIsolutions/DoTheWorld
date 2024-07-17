
#define DTW_DEBUG_TIME
#include "src/one.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *teste = dtw.resource.newResource("teste");
    /*
    DtwResource *sub_1 = dtw.resource.sub_resource(teste, "a");

    dtw.resource.set_string(sub_1, "sla");

    for(int i = 0; i < 20; i++){

        DtwResource *sub_1 = dtw.resource.sub_resource(teste, "%d", i);

        dtw.resource.set_string(sub_1, "sla");
    }
    */

    DtwResourceArray *list = dtw.resource.sub_resources(teste);

    for(int i = 0; i < list->size; i++){
        DtwResource *element = list->resources[i];

        char *path = element->name;

        printf("\n\tpath: %s\n", path);
    }
    dtw.resource.commit(teste);

}