#include "functions/list_dirs.c"
#include "functions/list_files.c"
#include "functions/list_all.c"
#include "functions/memory.c"

int main(int argc, char *argv[]){
    int size;
    char **dirs = cfm_list_all("exemple/", &size);
    for (int i = 0; i < size; i++) {
        printf("%s\n", dirs[i]);
    }
    cfm_free_string_array(dirs, size);
    
}