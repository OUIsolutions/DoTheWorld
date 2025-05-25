#include "doTheWorldOne.c"

int main() {
    DtwResource *values = new_DtwResource("tests/target");

    printf("elements:---------------------------------\n");
    DtwStringArray *sub_elements = DtwResource_list_names(values);
    DtwStringArray_sort(sub_elements);
    DtwStringArray_represent(sub_elements);
    DtwStringArray_free(sub_elements);
    printf("types:--------------------------------------\n");

    int type = DtwResource_type(values);

    if (type != DTW_FOLDER_TYPE) {
        printf("values its not an folder\n");
        DtwResource_free(values);
        return 1;
    }

    char *a = DtwResource_get_string_from_sub_resource(values, "a.txt");
    long blob_size;
    unsigned char *value = DtwResource_get_binary_from_sub_resource(values, &blob_size, "blob.png");
    DtwResource *numerical = DtwResource_sub_resource(values, "numerical");
    double double_value = DtwResource_get_double_from_sub_resource(numerical, "double.txt");
    long long_value = DtwResource_get_long_from_sub_resource(numerical, "integer.txt");
    bool bool_value = DtwResource_get_bool_from_sub_resource(numerical, "true_normal.txt");

    if (!DtwResource_error(values)) {
        printf("value string :%s\n", a);
        printf("blob size: %ld\n", blob_size);
        printf("double value %lf\n", double_value);
        printf("long value %ld\n", long_value);
        printf("bool value %d\n", bool_value);
    }
    if (DtwResource_error(values)) {
        char *message = DtwResource_get_error_message(values);
        printf("%s", message);
    }

    DtwResource_free(values);
    DtwResource_free(numerical);
}