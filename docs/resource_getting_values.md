

```c
#include "doTheWorldOne.c"

int main (){
    DtwResource *values = new_DtwResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray *sub_elements = DtwResource_list_names(values);
    DtwStringArray_sort(sub_elements);
    if(!DtwResource_error(values)){
        DtwStringArray_represent(sub_elements);
        DtwStringArray_free(sub_elements);
    }

    printf("types:--------------------------------------\n");

    DtwResource *string_r = DtwResource_sub_resource(values, "a.txt");
    char *string_r_value = DtwResource_get_string(string_r);
    DtwResource *blob_r = DtwResource_sub_resource(values, "blob.png");
    long blob_size;
    unsigned char *blob_r_value = DtwResource_get_binary(blob_r, &blob_size);

    DtwResource *numerical = DtwResource_sub_resource(values, "numerical");
    DtwResource *double_r = DtwResource_sub_resource(numerical, "double.txt");
    double double_r_value = DtwResource_get_double(double_r);

    DtwResource *long_r = DtwResource_sub_resource(numerical, "integer.txt");
    long long_r_value = DtwResource_get_long(long_r);
    DtwResource *bool_r = DtwResource_sub_resource(numerical, "true_normal.txt");
    bool bool_r_value = DtwResource_get_bool(bool_r);

    if(!DtwResource_error(values)){
        printf("value string :%s\n", string_r_value);
        printf("blob size: %ld\n", blob_r->value_size);
        printf("double value %lf\n", double_r_value);
        printf("long value %ld\n", long_r_value);
        printf("bool value %d\n", bool_r_value);
    }

    if(DtwResource_error(values)){
        char *message = DtwResource_get_error_message(values);
        printf("%s", message);
    }

    DtwResource_free(values);
}
```