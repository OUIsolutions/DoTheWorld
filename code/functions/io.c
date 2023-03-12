
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



char *dtw_load_any_content(const char * path,int *size,bool *is_binary){
    FILE *file = fopen(path,"rb");
    if(file == NULL){
        return NULL;
    }
    fseek(file,0,SEEK_END);
    *size = ftell(file);
    fseek(file,0,SEEK_SET);
    char *content = (char*)malloc(*size +1);
    fread(content,1,*size,file);

    *is_binary = false;
    for(int i = 0;i < *size;i++){
        if(content[i] == 0){
            *is_binary = true;
            break;
        }
    }
    if(!*is_binary){
        content[*size] = '\0';
    }

    fclose(file);
    return content;
}

char *dtw_load_string_file_content(const char * path){
    FILE *file = fopen(path,"rb");
    if(file == NULL){
        return NULL;
    }
    fseek(file,0,SEEK_END);
    int size = ftell(file);
    fseek(file,0,SEEK_SET);
    char *content = (char*)malloc(size +1);
    fread(content,1,size,file);
    content[size] = '\0';
    fclose(file);
    return content;
}

char *dtw_load_binary_contnt(const char * path,int *size){
    FILE *file = fopen(path,"rb");
    if(file == NULL){
        return NULL;
    }
    fseek(file,0,SEEK_END);
    *size = ftell(file);
    fseek(file,0,SEEK_SET);
    char *content = (char*)malloc(*size);
    fread(content,1,*size,file);
    fclose(file);
    return content;
}


bool dtw_write_any_content(const char *path,char *content,int size,bool create_dirs_if_not_exists){
    //Iterate through the path and create directories if they don't exist
    if(create_dirs_if_not_exists){
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
    }
    FILE *file = fopen(path,"wb");
    if(file == NULL){
        return false;
    }

    fwrite(content, sizeof(char),size, file);
    
    fclose(file);
    return true;
}

bool dtw_write_string_file_content(const char *path,char *content,bool create_dirs_if_not_exists){
    return dtw_write_any_content(path,content,strlen(content),create_dirs_if_not_exists);
}