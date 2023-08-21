#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray  *sub_elements = dtw.resource.list(values);
    dtw.string_array.represent(sub_elements);
    dtw.string_array.free(sub_elements);
    printf("types:--------------------------------------\n");

    if(values->type != DTW_FOLDER_TYPE){
        printf("values its not an folder\n");
        dtw.resource.free(values);
        return 1;
    }


    DtwResource *string_r = dtw.resource.sub_resource_loading(values, "a.txt");
    if(string_r->type == DTW_COMPLEX_STRING_TYPE){
        printf("value string :%s\n",string_r->value_string);
    }

    dtw.resource.free(string_r);


    DtwResource  *blob_r = dtw.resource.sub_resource_loading(values,"blob.png");
    if(blob_r->type == DTW_COMPLEX_BINARY){
        printf("blob size: %ld\n",blob_r->value_size);
    }

    dtw.resource.free(blob_r);



    DtwResource *numerical = dtw.resource.sub_resource_loading(values,"numerical");
    if(numerical->type == DTW_FOLDER_TYPE){
        DtwResource  *double_r = dtw.resource.sub_resource_loading(numerical,"double.txt");
        printf("double value %lf\n",double_r->value_double);
        dtw.resource.free(double_r);


        DtwResource  *long_r = dtw.resource.sub_resource_loading(numerical,"integer.txt");
        printf("long value %ld\n",long_r->value_long);
        dtw.resource.free(long_r);


        DtwResource  *bool_r = dtw.resource.sub_resource_loading(numerical,"true_normal.txt");
        printf("bool value %d\n",bool_r->value_bool);
        dtw.resource.free(bool_r);
    }





    dtw.resource.free(numerical);
    dtw.resource.free(values);



}





