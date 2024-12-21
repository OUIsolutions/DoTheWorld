#include "doTheWorld.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("testarget");

    printf("elements:---------------------------------\n");
    DtwStringArray  *sub_elements = dtw.resource.list_names(values);
    DtwStringArray_sort(sub_elements);

    dtw.string_array.represent(sub_elements);
    dtw.string_array.free(sub_elements);
    printf("types:--------------------------------------\n");




    int type  = dtw.resource.type(values);

    if(type != DTW_FOLDER_TYPE){
        printf("values its not an folder\n");
        dtw.resource.free(values);
        return 1;
    }

    char *a = dtw.resource.get_string_from_sub_resource(values,"a.txt");


    long blob_size;
    unsigned char *value  = dtw.resource.get_binary_from_sub_resource(values,&blob_size,"blob.png");


    DtwResource *numerical = dtw.resource.sub_resource(values,"numerical");
    double double_value = dtw.resource.get_double_from_sub_resource(numerical,"double.txt");
    long long_value = dtw.resource.get_long_from_sub_resource(numerical,"integer.txt");
    bool bool_value = dtw.resource.get_bool_from_sub_resource(numerical,"true_normal.txt");

    if(!dtw.resource.error(values)){
        printf("value string :%s\n",a);
        printf("blob size: %ld\n",blob_size);
        printf("double value %lf\n",double_value);
        printf("long value %ld\n",long_value);
        printf("bool value %d\n",bool_value);
    }
    if(dtw.resource.error(values)){
        char *message = DtwResource_get_error_message(values);
        printf("%s",message);
    }




    dtw.resource.free(values);



}





