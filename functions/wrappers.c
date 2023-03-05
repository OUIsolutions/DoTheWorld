#include "basic_list.c"

char **cfm_list_files(char *path, int *size){
    return cfm_list_basic(path, size, "file");
}

char **cfm_list_dirs(char *path, int *size){
    return cfm_list_basic(path, size, "dir");
}

char **cfm_list_all(char *path, int *size){
    return cfm_list_basic(path, size, "all");
}