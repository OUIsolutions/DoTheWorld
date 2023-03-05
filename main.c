#include "functions/wrappers.c"
#include "functions/list_dirs_recursively.c"
#include "functions/list_files_recursively.c"
#include "functions/extras.c"



int main(int argc, char *argv[]){
    int size;
    char **files = dtw_list_files_recursively("exemple", &size);
    for(int i = 0; i < size; i++){
        printf("%s\n", files[i]);
    }
}