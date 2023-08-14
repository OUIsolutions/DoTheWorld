#include "../../../doTheWorld_test.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray  *sub_elements = dtw.resource.list(values);
    dtw.string_array.represent(sub_elements);
    dtw.string_array.free(sub_elements);
    printf("types:--------------------------------------\n");

    int values_type = dtw.resource.type(values);
    if(values_type != DTW_FOLDER_TYPE){
        printf("values its not an folder\n");
        dtw.resource.free(values);
        return 1;
    }


    DtwResource *string_r = dtw.resource.sub_resource(values, "a.txt");
    char *value_of_string = dtw.resource.get_string(string_r);
    if(!value_of_string){
        printf("unable to locate a.txt\n");
        dtw.resource.free(values);
        dtw.resource.free(string_r);
        free(value_of_string);
        return 1;
    }
    printf("value string :%s\n",value_of_string);
    dtw.resource.free(string_r);
    free(value_of_string);

    DtwResource  *blob_r = dtw.resource.sub_resource(values,"blob.png");
    long size;
    bool is_binary;
    unsigned  char *blob_value = dtw.resource.get_any(blob_r,&size,&is_binary);
    printf("blob size: %ld, is_binary:%d\n",size,is_binary);
    free(blob_value);
    dtw.resource.free(blob_r);


    DtwResource *numerical = dtw.resource.sub_resource(values,"numerical");

    DtwResource  *double_r = dtw.resource.sub_resource(numerical,"double.txt");
    double  double_value = dtw.resource.get_double(double_r);
    printf("double value %lf\n",double_value);
    dtw.resource.free(double_r);


    DtwResource  *long_r = dtw.resource.sub_resource(numerical,"integer.txt");
    long  long_value = dtw.resource.get_long(long_r);
    printf("long value %ld\n",long_value);
    dtw.resource.free(long_r);


    DtwResource  *bool_r = dtw.resource.sub_resource(numerical,"true_normal.txt");
    bool bool_value = dtw.resource.get_bool(bool_r);
    printf("bool value %d\n",bool_value);
    dtw.resource.free(bool_r);


    dtw.resource.free(numerical);
    dtw.resource.free(values);



}





