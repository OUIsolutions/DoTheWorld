#include "../../../doTheWorld_test.h"

int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwResource *values = dtw.resource.newResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray  *sub_elements = dtw.resource.list_names(values);
    DtwStringArray_sort(sub_elements);
    if(!dtw.resource.error(values)){
        dtw.string_array.represent(sub_elements);
        dtw.string_array.free(sub_elements);
    }

    printf("types:--------------------------------------\n");

    DtwResource *string_r = dtw.resource.sub_resource(values, "a.txt");
    char *string_r_value = dtw.resource.get_string(string_r);
    DtwResource  *blob_r = dtw.resource.sub_resource(values,"blob.png");
    long blob_size;
    unsigned  char *blob_r_value = dtw.resource.get_binary(blob_r,&blob_size);

    DtwResource *numerical = dtw.resource.sub_resource(values,"numerical");
    DtwResource  *double_r = dtw.resource.sub_resource(numerical,"double.txt");
    double double_r_value = dtw.resource.get_double(double_r);

    DtwResource  *long_r = dtw.resource.sub_resource(numerical,"integer.txt");
    long long_r_value =dtw.resource.get_long(long_r);
    DtwResource  *bool_r = dtw.resource.sub_resource(numerical,"true_normal.txt");
    bool bool_r_value = dtw.resource.get_bool(bool_r);

    if(!dtw.resource.error(values)){
        printf("value string :%s\n",string_r_value);
        printf("blob size: %ld\n",blob_r->value_size);
        printf("double value %lf\n",double_r_value);
        printf("long value %ld\n",long_r_value);
        printf("bool value %d\n",bool_r_value);
    }

    if(!dtw.resource.error(values)){
        char *message = DtwResource_get_error_message(values);
        printf("%s",message);
    }



    dtw.resource.free(values);



}





