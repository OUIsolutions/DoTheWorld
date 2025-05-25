#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwStringArray *all = dtw_list_all("tests/target/", DTW_CONCAT_PATH);
    DtwStringArray_sort(all);
    DtwStringArray_represent(all);
    DtwStringArray_free(all);
    return 0;
}