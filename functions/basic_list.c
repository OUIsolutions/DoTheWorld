#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

char **cfm_list_basic(char *path, int *size,char* type){

    DIR *dir;
    struct dirent *entry;

    //array of directories
    char **dirs = calloc(1, sizeof(char *));
    int i = 0;

    //means that the directory is not found
    if ((dir = opendir(path)) == NULL) {
        *size = 0;
        return NULL;
    }

    //reads the directory and adds the directories to the array
    while ((entry = readdir(dir)) != NULL) {
        //means is not a directory
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        //means is a directory
        bool add = false;
        
        if (strcmp(type,"file") == 0 && entry->d_type == DT_REG) {
            add = true;
        }

        if (strcmp(type,"dir") == 0 && entry->d_type == DT_DIR) {
            add = true;
        }

        if (strcmp(type,"all") == 0) {
            add = true;
        }
        
        if (add) {
            
            //reallocates memory for the array
            dirs =  (char **)realloc(dirs, (i + 1) * sizeof(char *));
            
            //allocates memory for the directory
            dirs[i] = malloc((strlen(entry->d_name) + 1) * sizeof(char));
            
            //adds the directory to the array
            strcpy(dirs[i], entry->d_name);
            i++;
        }
    }

    //adds the size of the array
    *size = i;
    closedir(dir);

    return dirs;
}