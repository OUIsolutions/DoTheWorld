
#ifdef __linux__
#define create_dir(path) mkdir(path,0777)
#elif _WIN32
#define create_dir(path) _mkdir(path)
#endif

void dtw_create_dir_recursively(char *path){
    bool check = create_dir(path);
    char * current_path =  (char*)malloc(0);

    for(int i=0;i < strlen(path);i++){
        if(path[i] == '\\'  || path[i] == '/'   && i != strlen(path) - 1){
            current_path = (char*)realloc(current_path,i);
            current_path[i] = '\0';

            strncpy(current_path,path,i);
            create_dir(current_path);
        }
    }

    free(current_path);
    
    create_dir(path);
}


void dtw_create_file_recursively(char *path,char *content){
    
    for(int i = strlen(path)-1;i > 0;i--){
        if(path[i] == '\\' || path[i] == '/'){
            //make these work in c++
    
            char *dir_path =(char*)malloc(i);
            dir_path[i] = '\0';
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
