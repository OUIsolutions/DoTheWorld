#include "functions/wrappers.c"
#include "functions/extras.c"



int main(int argc, char *argv[]){
    int size;
    char **dirs = cfm_list_dirs("exemple/", &size);
    for (int i = 0; i < size; i++) {
        printf("%s\n", dirs[i]);
    }
    cfm_free_string_array(dirs, size);

}