#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwStringArray *files = dtw_list_files_recursively("tests/target/", DTW_CONCAT_PATH);
    DtwStringArray_sort(files);
    DtwStringArray_represent(files);
    DtwStringArray_free(files);
    return 0;
}