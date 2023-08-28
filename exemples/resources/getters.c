#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray  *sub_elements = dtw.resource.list_names(values);
    dtw.string_array.represent(sub_elements);
    dtw.string_array.free(sub_elements);
    printf("types:--------------------------------------\n");




    int type  = dtw.resource.type(values);

    if(type != DTW_FOLDER_TYPE){
        printf("values its not an folder\n");
        dtw.resource.free(values);
        return 1;
    }


    DtwResource *string_r = dtw.resource.sub_resource(values, "a.txt");
    if(dtw.resource.type(string_r) == DTW_COMPLEX_STRING_TYPE){
        printf("value string :%s\n",dtw.resource.get_string(string_r));
    }


    DtwResource  *blob_r = dtw.resource.sub_resource(values,"blob.png");
    if(dtw.resource.type(blob_r) == DTW_COMPLEX_BINARY){
        printf("blob size: %ld\n",blob_r->value_size);
    }




    DtwResource *numerical = dtw.resource.sub_resource(values,"numerical");
    if(dtw.resource.type(numerical) == DTW_FOLDER_TYPE){
        DtwResource  *double_r = dtw.resource.sub_resource(numerical,"double.txt");
        printf("double value %lf\n",dtw.resource.get_double(double_r));


        DtwResource  *long_r = dtw.resource.sub_resource(numerical,"integer.txt");
        printf("long value %ld\n",dtw.resource.get_long(long_r));


        DtwResource  *bool_r = dtw.resource.sub_resource(numerical,"true_normal.txt");
        printf("bool value %d\n",dtw.resource.get_bool(bool_r));
    }


    dtw.resource.free(values);



}





