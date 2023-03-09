#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32

#include <windows.h>

bool private_dtw_verify_if_add(const char *type, DWORD d_type){
    if (strcmp(type,"file") == 0 && d_type == FILE_ATTRIBUTE_NORMAL) {
        return true;
    }

    if (strcmp(type,"dir") == 0 && d_type == FILE_ATTRIBUTE_DIRECTORY) {
        return true;
    }

    if (strcmp(type,"all") == 0) {
        return true;
    }
    return false;
}

bool private_dtw_verify_if_skip(WIN32_FIND_DATAA *entry){
    if (strcmp(entry->cFileName, ".") == 0 || strcmp(entry->cFileName, "..") == 0) {
        return true;
    }
    return false;
}

struct DtwStringArray * dtw_list_basic(const char *path, const char* type, bool concat_path){

    WIN32_FIND_DATAA file_data;
    HANDLE file_handle;
    char search_path[MAX_PATH];

    //array of directories
    struct DtwStringArray *dirs = dtw_create_string_array();
    int i = 0;

    // build the search path string
    snprintf(search_path, MAX_PATH, "%s\\*", path);

    // try to open the directory
    if ((file_handle = FindFirstFileA(search_path, &file_data)) == INVALID_HANDLE_VALUE) {
        return dirs;
    }

    do {
        // skip "." and ".." directories
        if (private_dtw_verify_if_skip(&file_data)){
            continue;
        }

        // verify if it's a file or directory
        if (private_dtw_verify_if_add(type, file_data.dwFileAttributes)) {

            if(concat_path){
                // allocate memory for the directory
                char *generated_dir = (char*)malloc(strlen(path) + strlen(file_data.cFileName) + 2);
                sprintf(generated_dir, "%s\\%s", path, file_data.cFileName);
                dtw_add_string(dirs, generated_dir);
                free(generated_dir);
            }
            else{
                dtw_add_string(dirs, file_data.cFileName);
            }

            i++;
        }
    } while (FindNextFileA(file_handle, &file_data) != 0);

    FindClose(file_handle);

    return dirs;
}
#endif