#include "doTheWorld.h"


int main (){
    DtwNamespace dtw = newDtwNamespace();
    DtwResource *test = dtw.resource.newResource("testarget");

    DtwResource *next = dtw.resource.sub_resource_next(test,".txt");
    dtw.resource.set_string(next,"next-value");






    DtwResource *random = dtw.resource.sub_resource_random(test,".txt");
    dtw.resource.set_string(random,"random-value");


    DtwResource *now = dtw.resource.sub_resource_now(test,".txt");
    dtw.resource.set_string(now,"now value");


    DtwResource *now_in_unix = dtw.resource.sub_resource_now_in_unix(test,".txt");
    dtw.resource.set_string(now_in_unix,"now in unix");


    dtw.resource.commit(test);
    dtw.resource.free(test);

}






