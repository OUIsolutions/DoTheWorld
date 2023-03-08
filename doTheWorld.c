
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



struct DtwStringArray {
  int size;         
  int iterator;
  char **strings;       
}; // End the structure with a semicolon

struct DtwStringArray * dtw_create_string_array(){
    struct DtwStringArray *self = malloc(sizeof(struct DtwStringArray));
    self->size = 0;
    self->iterator = 0;
    self->strings = malloc(0);
    return self;
}


// Function prototypes
void dtw_add_string(struct DtwStringArray *self, char *string){
    self->size++;
    self->strings = realloc(self->strings, self->size * sizeof(char *));
    self->strings[self->size - 1] = malloc(strlen(string) + 1);
    strcpy(self->strings[self->size - 1], string);
}

void dtw_append_string_array(struct DtwStringArray *self, struct DtwStringArray *other){
    for(int i = 0; i < other->size; i++){
        dtw_add_string(self, other->strings[i]);
    }
}


void dtw_represent_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        printf("%s\n", self->strings[i]);
    }
}
void dtw_free_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        free(self->strings[i]);
    }
    free(self->strings);

    free(self);
}
//


// 
struct DtwStringArray * dtw_list_files(char *path, bool concat_path){
    //


bool verify_if_add(char *type, int d_type){
    if (strcmp(type,"file") == 0 && d_type == DT_REG) {
        return true;
    }

    if (strcmp(type,"dir") == 0 && d_type == DT_DIR) {
        return true;
    }

    if (strcmp(type,"all") == 0) {
        return true;
    }
    return false;
}
bool verify_if_skip(struct dirent *entry){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            return true;
        }
        return false;
}

struct DtwStringArray * dtw_list_basic(char *path,char* type,bool concat_path){

    DIR *dir;
    struct dirent *entry;

    //array of directories
    struct DtwStringArray *dirs = dtw_create_string_array();
    int i = 0;

    //means that the directory is not found
    if ((dir = opendir(path)) == NULL) {
        return dirs;
    }

    //reads the directory and adds the directories to the array
    while ((entry = readdir(dir)) != NULL) {
        //means is not a directory
        if (verify_if_skip(entry)){
            continue;
        }
    
        if (verify_if_add(type,entry->d_type)) {
            
            
            if(concat_path){
                //allocates memory for the directory
                char *generated_dir = malloc(strlen(path) + strlen(entry->d_name) + 2);
                sprintf(generated_dir, "%s/%s", path, entry->d_name);
                dtw_add_string(dirs, generated_dir);
                free(generated_dir);

            }
            else{
                dtw_add_string(dirs, entry->d_name);
            }

            i++;
        }
    }

  
    closedir(dir);

    return dirs;
}
//
    return dtw_list_basic(path,  "file", concat_path);
}

struct DtwStringArray * dtw_list_dirs(char *path, bool concat_path){
     //


bool verify_if_add(char *type, int d_type){
    if (strcmp(type,"file") == 0 && d_type == DT_REG) {
        return true;
    }

    if (strcmp(type,"dir") == 0 && d_type == DT_DIR) {
        return true;
    }

    if (strcmp(type,"all") == 0) {
        return true;
    }
    return false;
}
bool verify_if_skip(struct dirent *entry){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            return true;
        }
        return false;
}

struct DtwStringArray * dtw_list_basic(char *path,char* type,bool concat_path){

    DIR *dir;
    struct dirent *entry;

    //array of directories
    struct DtwStringArray *dirs = dtw_create_string_array();
    int i = 0;

    //means that the directory is not found
    if ((dir = opendir(path)) == NULL) {
        return dirs;
    }

    //reads the directory and adds the directories to the array
    while ((entry = readdir(dir)) != NULL) {
        //means is not a directory
        if (verify_if_skip(entry)){
            continue;
        }
    
        if (verify_if_add(type,entry->d_type)) {
            
            
            if(concat_path){
                //allocates memory for the directory
                char *generated_dir = malloc(strlen(path) + strlen(entry->d_name) + 2);
                sprintf(generated_dir, "%s/%s", path, entry->d_name);
                dtw_add_string(dirs, generated_dir);
                free(generated_dir);

            }
            else{
                dtw_add_string(dirs, entry->d_name);
            }

            i++;
        }
    }

  
    closedir(dir);

    return dirs;
}
//
    return dtw_list_basic(path,"dir", concat_path);
}

struct DtwStringArray *  dtw_list_all(char *path,  bool concat_path){
    //


bool verify_if_add(char *type, int d_type){
    if (strcmp(type,"file") == 0 && d_type == DT_REG) {
        return true;
    }

    if (strcmp(type,"dir") == 0 && d_type == DT_DIR) {
        return true;
    }

    if (strcmp(type,"all") == 0) {
        return true;
    }
    return false;
}
bool verify_if_skip(struct dirent *entry){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            return true;
        }
        return false;
}

struct DtwStringArray * dtw_list_basic(char *path,char* type,bool concat_path){

    DIR *dir;
    struct dirent *entry;

    //array of directories
    struct DtwStringArray *dirs = dtw_create_string_array();
    int i = 0;

    //means that the directory is not found
    if ((dir = opendir(path)) == NULL) {
        return dirs;
    }

    //reads the directory and adds the directories to the array
    while ((entry = readdir(dir)) != NULL) {
        //means is not a directory
        if (verify_if_skip(entry)){
            continue;
        }
    
        if (verify_if_add(type,entry->d_type)) {
            
            
            if(concat_path){
                //allocates memory for the directory
                char *generated_dir = malloc(strlen(path) + strlen(entry->d_name) + 2);
                sprintf(generated_dir, "%s/%s", path, entry->d_name);
                dtw_add_string(dirs, generated_dir);
                free(generated_dir);

            }
            else{
                dtw_add_string(dirs, entry->d_name);
            }

            i++;
        }
    }

  
    closedir(dir);

    return dirs;
}
//
    return dtw_list_basic(path, "all", concat_path);
}
//