

struct DtwPath * newDtwPath(const char *path) {
    struct DtwPath *self = (struct DtwPath *)malloc(sizeof(struct DtwPath));

    self->dir = (char *)malloc(0);
    self->name = (char *)malloc(0);
    self->extension = (char *)malloc(0);
    self->dir_exists = false;
    self->name_exists = false;
    self->extension_exists = false;

    self->garbage = newDtwStringArray();


    DtwPath_set_path(self, path);
    self->original_path = DtwPath_get_path(self);
    
    return self;
}
bool DtwPath_changed(struct DtwPath *self){

    char *path = DtwPath_get_path(self);
    if(!path && !self->original_path){
        return  false;
    }
    if(!path && self->original_path){
        return true;
    }

    if(path && !self->original_path){
        return true;
    }

    if(strcmp(self->original_path,path ) == 0){
        return false;
    }
    return true;
}


char * DtwPath_get_name(struct DtwPath *self){
    if(self->name_exists == false){
        return NULL;
    }

    char *name = strdup(self->name);
    DtwStringArray_append_getting_ownership(self->garbage,name);

    return name;
}
char * DtwPath_get_extension(struct DtwPath *self){
    if(self->extension_exists == false){
        return NULL;
    }
    char *extension = strdup(self->extension);
    DtwStringArray_append_getting_ownership(self->garbage,extension);
    return extension;   
}

char * DtwPath_get_full_name(struct DtwPath *self){
    char *full_name = NULL;
    if(self->name_exists == true &&  self->extension_exists == true){
        full_name = (char *)malloc(strlen(self->name) + strlen(self->extension) + 2);
        sprintf(full_name, "%s.%s",self->name, self->extension);
    }

    if(self->name_exists == true &&  self->extension_exists == false){
        full_name = strdup(self->name);
    }
    
    if(self->name_exists == false &&  self->extension_exists == true){
        full_name = strdup(self->extension);
        
    }   
    if(full_name){
        DtwStringArray_append_getting_ownership(self->garbage,full_name);
    } 
    return full_name;
}

char * DtwPath_get_dir(struct DtwPath *self){
    if(self->dir_exists == false){
        return NULL;
    }
    char *dir = strdup(self->dir);
    DtwStringArray_append_getting_ownership(self->garbage,dir);
    return dir;
}

char * DtwPath_get_path(struct DtwPath *self){
    //concat the path, name and extension with / 
    char *full_name = DtwPath_get_full_name(self);
    char *dir = DtwPath_get_dir(self);

    #define FULL_NAME_EXIST full_name != NULL
    #define FULL_NAME_NOT_EXIST full_name == NULL
    #define DIR_EXIST dir != NULL
    #define DIR_NOT_EXIST dir == NULL
    char *path = NULL;
    if(FULL_NAME_EXIST && DIR_EXIST){
        path = dtw_concat_path(dir, full_name);
        DtwStringArray_append_getting_ownership(self->garbage,path);
    }
    if(FULL_NAME_EXIST && DIR_NOT_EXIST){
        path = strdup(full_name);
        DtwStringArray_append_getting_ownership(self->garbage,path);

    }
    if(FULL_NAME_NOT_EXIST && DIR_EXIST){
        char *path = dtw_concat_path(dir, "");
        DtwStringArray_append_getting_ownership(self->garbage,path);
    }
    
    return path;
}



void DtwPath_set_extension(struct DtwPath *self, const char *extension){
    if(strcmp(extension, "") == 0){
        return;
    }
    self->extension_exists = true;
    int extension_size = strlen(extension);
    self->extension = (char *)realloc(self->extension, extension_size+2);
    strcpy(self->extension, extension);
    self->extension[extension_size] = '\0';
}


void DtwPath_set_name(struct DtwPath * self, const char * name){
    if(strcmp(name, "") == 0){
        return;
    }
    self->name_exists = true;
    int name_size = strlen(name);
    self->name = (char *)realloc(self->name, name_size +1);
   
    strcpy(self->name, name);
    self->name[name_size] = '\0';
}



void DtwPath_set_full_name(struct DtwPath * self, const char * full_name){
    self->name_exists = false;
    self->extension_exists = false;

    int full_name_size = strlen(full_name);
    for(int i = 0; i < full_name_size; i++){
        if(full_name[i] == '.'){
            int name_size = i;
            int extension_size = full_name_size - i - 1;

            char *name = (char *)malloc(name_size + 1);
            strncpy(name, full_name, name_size);
            name[name_size] = '\0';
            DtwPath_set_name(self, name);
            free(name);

            char *extension = (char *)malloc(extension_size + 1);
            strncpy(extension, full_name + i + 1, extension_size);
            extension[extension_size] = '\0';
            DtwPath_set_extension(self, extension);
            free(extension);
            return;
        }
    }
    DtwPath_set_name(self, full_name);
}


void DtwPath_set_dir(struct DtwPath *self, const char *path){
    if(strcmp(path, "") == 0){
        return;
    }
    self->dir_exists = true;
    int path_size = strlen(path);
    self->dir = (char *)realloc(self->dir, path_size+1);
    strcpy(self->dir, path);
    self->dir[path_size] = '\0';
}

void DtwPath_set_path(struct DtwPath *self, const char *target_path) {
    self->dir_exists = false;
    self->name_exists = false;
    self->extension_exists = false;
    
    int path_size = strlen(target_path);
  
    for(int i = path_size - 1; i >= 0; i--){
        if(target_path[i] == '/' || target_path[i] == '\\'){
            
            char *path = (char *)malloc(i + 1);
            strncpy(path, target_path, i);
            path[i] = '\0';
            DtwPath_set_dir(self, path);
            free(path);

            char *full_name = (char *)malloc(path_size - i);
            strcpy(full_name, target_path + i + 1);
            full_name[path_size - i - 1] = '\0';
            DtwPath_set_full_name(self, full_name);
            free(full_name);
            return;
        }
    }

    DtwPath_set_full_name(self, target_path);
}

void DtwPath_add_start_dir(struct DtwPath *self, const char *start_dir){

    char *dir = DtwPath_get_dir(self);
    //concat the path, with start_dir at beguining
    if(dir != NULL){
        char *path = dtw_concat_path(start_dir, dir);
        DtwPath_set_dir(self, path);
        free(path);
    }
    else{
        DtwPath_set_dir(self,start_dir);
    }
}

void DtwPath_add_end_dir(struct DtwPath *self, const char *end_dir){
    char *dir = DtwPath_get_dir(self);
    //concat the path, with start_dir at beguining
    if(dir != NULL){
        char *path = dtw_concat_path(dir, end_dir);
        DtwPath_set_dir(self, path);
        free(path);
    }
    else{
        DtwPath_set_dir(self,end_dir);
    }
}

  

void DtwPath_represent(struct DtwPath *self){
    char  *path = DtwPath_get_path(self);
    char *full_name = DtwPath_get_full_name(self);
    char *dir = DtwPath_get_dir(self);
    char *name = DtwPath_get_name(self);
    char *extension = DtwPath_get_extension(self);
    bool changed = DtwPath_changed(self);

    printf("First Path: %s\n", self->original_path ? self->original_path : "NULL");
    printf("Path: %s\n", path  ? path : "NULL");
    printf("Path Changed: %s\n", changed ? "true" : "false");
    printf("Dir: %s\n", dir ? dir : "NULL");
    printf("Full Name: %s\n", full_name ? full_name : "NULL");
    printf("Name: %s\n", name ? name : "NULL");
    printf("Extension: %s\n", extension ? extension : "NULL");

    
}



void DtwPath_free(struct DtwPath *self) {
    DtwStringArray_free(self->garbage);
    free(self->dir);
    free(self->name);
    free(self->extension);
    free(self);
}

