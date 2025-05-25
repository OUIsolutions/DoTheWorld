#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwStringArray *dirs = dtw_list_dirs("tests/target", DTW_NOT_CONCAT_PATH);
    //the represent method will print the dirs in the console
    DtwStringArray_sort(dirs);
    DtwStringArray_represent(dirs);
    DtwStringArray_free(dirs);
    return 0;
}