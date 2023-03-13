
#ifdef __linux__
#define create_dir(path) mkdir(path,0777)
#elif _WIN32
#define create_dir(path) _mkdir(path)
#endif



void dtw_create_dir_recursively(char *path){
    bool check = create_dir(path);
    char * current_path =  (char*)malloc(0);
    int size_path = strlen(path);
    for(int i=0;i <  size_path;i++){
        if(path[i] == '\\'  || path[i] == '/'   && i != size_path - 1){
            current_path = (char*)realloc(current_path,i);
            current_path[i] = '\0';
            //set current path at i position
            strncpy(current_path,path,i);
            create_dir(current_path);
        }
    }

    free(current_path);
    
    create_dir(path);
}


void dtw_remove_any(char* path) {

    if(remove(path) == 0){
        return;
    }
    
    struct DtwStringArray *files = dtw_list_files_recursively(path);
    int size = files->size;
    for(int i = 0; i < size; i++){
        remove(files->strings[i]);
    }
    files->delete(files);


    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path,true);
    size = dirs->size;
    for(int i = dirs->size -1; i >=0; i--){
        remove(dirs->strings[i]);
    }
    dirs->delete(dirs);
    
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


char *dtw_load_binary_content(const char * path,int *size){
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


bool dtw_write_any_content(const char *path,const char *content,int size){
    //Iterate through the path and create directories if they don't exist
    
    for(int i = strlen(path)-1;i > 0;i--){
        //runs in negative mode til / or \ is found
        if(path[i] == '\\' || path[i] == '/'){
            char *dir_path =(char*)malloc(i);
            dir_path[i] = '\0';
            strncpy(dir_path,path,i);
            
            dtw_create_dir_recursively(dir_path);
            free(dir_path);
        
            break;
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


bool dtw_write_string_file_content(const char *path,char *content){
    return dtw_write_any_content(path,content,strlen(content));
}

int dtw_entity_type(const char *path){
    //returns 1 for file, 2 for directory, -1 for not found
    struct stat path_stat; 

    if(stat(path,&path_stat) == 0){
        if(S_ISREG(path_stat.st_mode)){
            return DTW_FILE_TYPE;
        }else if(S_ISDIR(path_stat.st_mode)){
            return DTW_FOLDER_TYPE;
        }
    }
    return NOT_FOUND;
}

bool dtw_copy_any(char* src_path, char* dest_path,bool merge) {

    //verify if is an file 

    int type = dtw_entity_type(src_path);
    if(type == NOT_FOUND){
        return false;
    }

    if(type == DTW_FILE_TYPE){
    
        int size;
        bool is_binary;
        char *content = dtw_load_any_content(src_path,&size,&is_binary);
        bool result =  dtw_write_any_content(dest_path,content,size);
        free(content);
        return result;
    }
    //means is an directory
    

    if(!merge){
        dtw_remove_any(dest_path);
    }
    struct DtwStringArray *dirs = dtw_list_dirs_recursively(src_path,true);
    int size = dirs->size;
    int size_to_remove = strlen(src_path);
    for(int i = 0; i < size; i++){
        char *new_dir = dtw_change_beginning_of_string(dirs->strings[i],size_to_remove,dest_path);
        dtw_create_dir_recursively(new_dir);
        free(new_dir);
    }   
    dirs->delete(dirs);
    struct DtwStringArray *files = dtw_list_files_recursively(src_path);
    size = files->size;
    for(int i = 0; i < size; i++){
        int file_size;
        bool is_binary;
        char *content = dtw_load_any_content(files->strings[i],&file_size,&is_binary);
        char *new_file = dtw_change_beginning_of_string(files->strings[i],size_to_remove,dest_path);
        dtw_write_any_content(new_file,content,file_size);
        free(content);
        free(new_file);
    }
    files->delete(files);
    return true;
}

void dtw_move_any(char* src_path, char* dest_path,bool merge) {
    dtw_copy_any(src_path,dest_path,merge);
    dtw_remove_any(src_path);
}
