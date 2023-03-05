#include "functions/list_dirs.c"

int main(int argc, char *argv[]){
    int size;
    char **dirs = cfm_list_dirs("exemple", &size);
    for (int i = 0; i < size; i++) {
        printf("%s\n", dirs[i]);
    }

}