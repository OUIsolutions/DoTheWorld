#include "functions/listage_wrappers.c"

int main(int argc, char *argv[]){
    
    struct DtwStringArray *array = dtw_list_dirs("exemple",true);
    dtw_represent_string_array(array);

}