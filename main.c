#include "structs/string_array.c"
int main(int argc, char *argv[]){
    
    struct DtwStringArray *array = dtw_create_string_array();
    dtw_add_string(array, "Hello");
    dtw_add_string(array, "World");
    dtw_represent_string_array(array);
    dtw_free_string_array(array);
    return 0;


}