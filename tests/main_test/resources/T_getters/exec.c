#include "../../../doTheWorld_test.h"

int main (){

    DtwResource *values = new_DtwResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray  *sub_elements = values->list(values);
    sub_elements->represent(sub_elements);
    sub_elements->free(sub_elements);
    printf("types:--------------------------------------\n");

    int values_type = values->type(values);
    if(values_type != DTW_FOLDER_TYPE){
        printf("values its not an folder\n");
        values->free(values);
        return 1;
    }


    DtwResource *string_r = values->sub_resource(values, "a.txt");
    char *value_of_string = string_r->get_string(string_r);
    if(!value_of_string){
        printf("unable to locate a.txt\n");
        values->free(values);
        string_r->free(string_r);
        free(value_of_string);
        return 1;
    }
    printf("value string :%s\n",value_of_string);
    string_r->free(string_r);
    free(value_of_string);

    DtwResource  *blob_r = values->sub_resource(values,"blob.png");
    long size;
    bool is_binary;
    unsigned  char *blob_value = blob_r->get_any(blob_r,&size,&is_binary);
    printf("blob size: %ld, is_binary:%d\n",size,is_binary);
    free(blob_value);
    blob_r->free(blob_r);


    DtwResource *numerical = values->sub_resource(values,"numerical");

    DtwResource  *double_r = numerical->sub_resource(numerical,"double.txt");
    double  double_value = double_r->get_double(double_r);
    printf("double value %lf\n",double_value);
    double_r->free(double_r);


    DtwResource  *long_r = numerical->sub_resource(numerical,"integer.txt");
    long  long_value = long_r->get_long(long_r);
    printf("long value %ld\n",long_value);
    long_r->free(long_r);


    DtwResource  *bool_r = numerical->sub_resource(numerical,"true_normal.txt");
    bool bool_value = bool_r->get_bool(bool_r);
    printf("bool value %d\n",bool_value);
    bool_r->free(bool_r);


    numerical->free(numerical);
    values->free(values);



}





