
#ifdef __linux__

void dtw_create_dir_recursively(char *path){
    bool check = mkdir(path, 0777);
    char * current_path =  (char*)malloc(0);
    for(int i=0;i < strlen(path);i++){
        
        if(path[i] == '/' && i != strlen(path) - 1){
            current_path = (char*)realloc(current_path,i);
            strncpy(current_path,path,i);
            mkdir(current_path, 0777);
        }
    }
    free(current_path);
    
    mkdir(path, 0777);
}
#elif _WIN32
void dtw_create_dir_recursively(char *path){
    CreateDirectory(path,NULL);
}
#endif

void dtw_create_file_recursively(char *path,char *content){
    for(int i = strlen(path)-1;i > 0;i--){
        if(path[i] == '/'){
            //make these work in c++
            
            char *dir_path =(char*)malloc(i);

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
