
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void dtw_create_dir_recursively(char *path){
    bool check = mkdir(path, 0777);
    char current_path[100];
    for(int i=0;i < strlen(path);i++){
        
        if(path[i] == '/' && i != strlen(path) - 1){
            strncpy(current_path,path,i);
            mkdir(current_path, 0777);
        }
    }
    
    mkdir(path, 0777);
}
