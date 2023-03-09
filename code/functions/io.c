
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


bool  dtw_write_file_recursively(char *path,unsigned char *content,int size){
    
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
    FILE *file = fopen(path,"wb");
    if(file == NULL){
        return false;
    }

    if(size != 0){
           //its not possible to determine an binary length
          fwrite(content, sizeof(unsigned char),size, file);
    }
    else{
        fwrite(content, sizeof(unsigned char),strlen(content), file);
    }
    fclose(file);
    return true;
}


char * dtw_load_file_content(char * path,int *size,bool *is_binary){
    FILE *file = fopen(path,"rb");
    if(file == NULL){
        return NULL;
    }
    fseek(file,0,SEEK_END);
    size = ftell(file);
    fseek(file,0,SEEK_SET);
    unsigned char *content = (unsigned char*)malloc(size +1);
    fread(content,1,size,file);
    //Detect if binary
    printf("size: %d",size);
    is_binary = false;

    for(int i = 0; i < size; i++){
        if(content[i] == 0){
            is_binary = true;
            break;
        }
    }

    if(is_binary == false){
            content[*size] = '\0';
    }


    fclose(file);
    return content;
}

