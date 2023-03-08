
#include "../imports.c"
//{% macro writing() %}
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


void dtw_create_file_recursively(char *path,char *content){
    for(int i = strlen(path)-1;i > 0;i--){
        if(path[i] == '/'){
            char *dir_path = malloc(i);
            strncpy(dir_path,path,i);
            
            dtw_create_dir_recursively(dir_path);
            free(dir_path);
        
            break;
        }
    }
    FILE *file = fopen(path,"w");
    fprintf(file,"%s",content);
    fclose(file);

}
//{% endmacro %}