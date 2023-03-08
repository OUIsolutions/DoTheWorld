
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void dtw_create_dir_recursively(char *path){
    bool check = mkdir(path, 0777);
    char * current_path = malloc(0);
    for(int i=0;i < strlen(path);i++){
        
        if(path[i] == '/' && i != strlen(path) - 1){
            current_path = realloc(current_path,i);
            strncpy(current_path,path,i);
            mkdir(current_path, 0777);
        }
    }
    free(current_path);
    
    mkdir(path, 0777);
}


void create_file_recursively(char *path,char *content){
    
}