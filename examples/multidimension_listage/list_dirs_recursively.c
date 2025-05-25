#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();  // Keep this as it's the initialization, but we're replacing calls

    DtwStringArray *files = dtw_list_dirs_recursively("tests/target/", DTW_CONCAT_PATH);
    DtwStringArray_sort(files);
    DtwStringArray_represent(files);
    DtwStringArray_free(files);
    
    return 0;
}