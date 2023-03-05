#include "monodimension_listage.c" 

char **cfm_list_files(char *path, int *size, bool concat_path){
    return cfm_list_basic(path, size, "file", concat_path);
}

char **cfm_list_dirs(char *path, int *size, bool concat_path){
    return cfm_list_basic(path, size, "dir", concat_path);
}

char **cfm_list_all(char *path, int *size, bool concat_path){
    return cfm_list_basic(path, size, "all", concat_path);
}