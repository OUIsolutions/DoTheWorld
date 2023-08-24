#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target");

    //when you set caches to false, it will not store sub resources
    values->cache_sub_resources = false;

    DtwResource *string_r = dtw.resource.sub_resource(values, "a.txt");
    if(dtw.resource.type(string_r) == DTW_COMPLEX_STRING_TYPE){
        printf("value string :%s\n",dtw.resource.get_string(string_r));
    }
    dtw.resource.free(string_r);

    values->cache_sub_resources = true;
    
    //when allowing transaction to false, it will execute now 
    values->allow_transaction = false;
    DtwResource *string_r1 = dtw.resource.sub_resource(values, "b.txt");
    dtw.resource.set_string(string_r1,"menssage");
    



    dtw.resource.free(values);



}





