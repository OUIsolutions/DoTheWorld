#include "functions/multidimension_listage.c"

int main(int argc, char *argv[]){
    
    struct DtwStringArray *array = dtw_list_dirs_recursively("exemple");
    dtw_represent_string_array(array);

}