#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


char **cfm_list_dirs(char *path, int *size){

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
        if (entry->d_type == DT_DIR) {
            
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