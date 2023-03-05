#include "list_dirs_recursively.c"

char ** dtw_list_files_recursively(char *path, int *size){

    char **dirs = dtw_list_dirs_recursively(path, size);
    char **files = calloc(1, sizeof(char *));
    int sub_files_size = 0;
    for(int i = 0; i < *size; i++){
      int current_sub_files_size;
      char **sub_files = dtw_list_basic(dirs[i], &current_sub_files_size, "file", true);

      dtw_append_string_array_in_other(&files, &sub_files_size, sub_files, current_sub_files_size);
       
    }
    
    dtw_free_string_array(dirs, *size);
    *size = sub_files_size;
    return files;
}