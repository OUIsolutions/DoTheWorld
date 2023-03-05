#include "functions/wrappers.c"
#include "functions/list_dirs_recursively.c"
#include "functions/extras.c"



int main(int argc, char *argv[]){
    int size;
    char **dirs = cfm_list_dirs_recursively("exemple", &size);
    for(int i = 0; i < size; i++){
        printf("%s\n", dirs[i]);
    }
}