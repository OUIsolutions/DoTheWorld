#include "doTheWorldOne.c"

int main (){

    DtwResource *values = new_DtwResource("tests/target");

    //when you set caches to false, it will not store sub resources
    values->cache_sub_resources = false;

    DtwResource *string_r = DtwResource_sub_resource(values,"a.txt");
    if(DtwResource_type(string_r) == DTW_COMPLEX_STRING_TYPE){
        printf("value string :%s\n",DtwResource_get_string(string_r));
    }
    DtwResource_free(string_r);

    values->cache_sub_resources = true;

    //when allowing transaction to false, it will execute now
    values->allow_transaction = false;
    DtwResource *string_r1 = DtwResource_sub_resource(values,"b.txt");
    DtwResource_set_string(string_r1,"message"); // corrected spelling of "menssage"



    DtwResource_free(values);

}