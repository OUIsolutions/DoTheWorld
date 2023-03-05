#include "monodimension_listage.c" 

char **dtw_list_files(char *path, int *size, bool concat_path){
    return dtw_list_basic(path, size, "file", concat_path);
}

char **dtw_list_dirs(char *path, int *size, bool concat_path){
    return dtw_list_basic(path, size, "dir", concat_path);
}

char **dtw_list_all(char *path, int *size, bool concat_path){
    return dtw_list_basic(path, size, "all", concat_path);
}