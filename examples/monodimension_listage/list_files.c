#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
    DtwStringArray *files = dtw_list_files("tests/target", DTW_CONCAT_PATH);
    DtwStringArray_sort(files);

    for(int i = 0; i < files->size; i++){
        printf("%s\n", files->strings[i]);
    }
    DtwStringArray_free(files);
    return 0;
}