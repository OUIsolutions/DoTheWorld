

struct DtwPath * dtw_constructor_path( const char *full_path) {
    struct DtwPath *self = (struct DtwPath *)malloc(sizeof(struct DtwPath));

    self->dir = (char *)malloc(0);
    self->name = (char *)malloc(0);
    self->extension = (char *)malloc(0);


    self->changed = private_dtw_path_changed;
    self->get_full_name =private_dtw_get_full_name;
    self->get_name = private_dtw_get_name;
    self->get_extension = private_dtw_get_extension;


    self->get_full_path = private_dtw_get_full_path;
    self->get_dir = private_dtw_get_dir;

    self->set_extension = private_dtw_set_extension;
    self->set_name = private_dtw_set_name;
    self->set_dir = private_dtw_set_dir;
    self->set_full_name = private_dtw_set_full_name;
    self->set_full_path = private_dtw_set_full_path;

    self->represent = private_dtw_represent_path;
    self->delete_path = private_dtw_destructor_path;

    self->set_full_path(self, full_path);
    self->first_full_path = self->get_full_path(self);
    
    return self;
}
bool private_dtw_path_changed(struct DtwPath *self){
    if(strcmp(self->first_full_path, self->get_full_path(self)) == 0){
        return false;
    }
    return true;
}


char * private_dtw_get_name(struct DtwPath *self){
    if(strcmp(self->name, "") == 0){
        return NULL;
    }
    return self->name;
}
char * private_dtw_get_extension(struct DtwPath *self){
    if(strcmp(self->extension, "") == 0){
        return NULL;
    }
    return self->extension;
}

char * private_dtw_get_full_name(struct DtwPath *self){
    char *full_name = (char *)malloc(strlen(self->name) + strlen(self->extension) +1);
    //concat the name and extension with / 
    //if the extension is empty, then the full name is just the name
    char *extension = self->get_extension(self);
    char *name = self->get_name(self);

    if(extension == NULL && name != NULL){
        sprintf(full_name, "%s",name);
    }
    
    if(extension != NULL &&  name == NULL){
        sprintf(full_name, "%s",extension);
    }

    if(extension != NULL && name != NULL){
        sprintf(full_name, "%s.%s",name, extension);
    }
    if(extension == NULL && name == NULL){
        free(full_name);
        return NULL;
    }
    return full_name;


}
char * private_dtw_get_dir(struct DtwPath *self){
    if(strcmp(self->dir, "") == 0){
        return NULL;
    }
    return self->dir;
}

char * private_dtw_get_full_path(struct DtwPath *self){
    char *full_path = (char *)malloc(strlen(self->dir) + strlen(self->name) + strlen(self->extension) +3);
    //concat the path, name and extension with / 
    char *full_name = self->get_full_name(self);
    char *dir = self->get_dir(self);
    #define FULL_NAME_EXIST full_name != NULL
    #define FULL_NAME_NOT_EXIST full_name == NULL
    #define DIR_EXIST dir != NULL
    #define DIR_NOT_EXIST dir == NULL
    if(FULL_NAME_EXIST && DIR_EXIST){
        sprintf(full_path, "%s/%s",dir,full_name);
    }
    if(FULL_NAME_EXIST && DIR_NOT_EXIST){
        sprintf(full_path, "%s",full_name);
    }
    if(FULL_NAME_NOT_EXIST && DIR_EXIST){
        sprintf(full_path, "%s",dir);
    }
    if(FULL_NAME_NOT_EXIST && DIR_NOT_EXIST){
        free(full_path);
        free(full_name);
        return NULL;
    }

    free(full_name);
    return full_path;
}



void private_dtw_set_extension(struct DtwPath *self, const char *extension){
    if(strcmp(extension, "") == 0){
        return;
    }
    int extension_size = strlen(extension);
    self->extension = (char *)realloc(self->extension, extension_size);
    strcpy(self->extension, extension);
    self->extension[extension_size] = '\0';
}


void private_dtw_set_name(struct DtwPath * self, const char * name){
    if(strcmp(name, "") == 0){
        return;
    }
    int name_size = strlen(name);
    self->name = (char *)realloc(self->name, name_size);
    strcpy(self->name, name);
    self->name[name_size] = '\0';
}



void private_dtw_set_full_name(struct DtwPath * self, const char * full_name){
    
    for(int i = 0; i < strlen(full_name); i++){
        if(full_name[i] == '.'){
            char *name = (char *)malloc(i);
            //substr the name from the start to the current position
            strncpy(name, full_name, i);
            self->set_name(self, name);
            free(name);
            //substr the extension from the current position to the end
            char *extension = (char *)malloc(strlen(full_name) - i);
            strcpy(extension, full_name + i + 1);
            self->set_extension(self, extension);
            free(extension);
            return;
        }
    }
    self->set_name(self, full_name);
    
}


void private_dtw_set_dir(struct DtwPath *self, const char *path){
    if(strcmp(path, "") == 0){
        return;
    }
    int path_size = strlen(path);
    self->dir = (char *)realloc(self->dir, path_size+1);
    strcpy(self->dir, path);
    self->dir[path_size] = '\0';
}

void private_dtw_set_full_path(struct DtwPath *self, const char *ful_path) {

    
    int full_path_size = strlen(ful_path);
  
    //lopos in n
    for(int i = full_path_size ;i >0; i--){
   
        if(ful_path[i] == '/' || ful_path[i] == '\\'){
            
            char *path = (char *)malloc(i);
            //substr the path from the start to the current position
            strncpy(path, ful_path, i);
            self->set_dir(self, path);
            free(path);

            //substr the name from the current position to the end
            char *name = (char *)malloc(full_path_size - i);
            strcpy(name, ful_path + i + 1);
            self->set_full_name(self, name);
            free(name);
            return;
        }
    }

    self->set_full_name(self, ful_path);

}


void private_dtw_represent_path(struct DtwPath *self){
    char  *full_path = self->get_full_path(self);
    char *full_name = self->get_full_name(self);
    char *dir = self->get_dir(self);
    char *name = self->get_name(self);
    char *extension = self->get_extension(self);
    printf("First Full Path: %s\n", self->first_full_path ? self->first_full_path : "NULL");
    printf("Full Path: %s\n", full_path  ? full_path : "NULL");
    printf("Changed: %s\n", self->changed(self) ? "true" : "false");
    printf("Dir: %s\n", dir ? dir : "NULL");
    printf("Full Name: %s\n", full_name ? full_name : "NULL");
    printf("Name: %s\n", name ? name : "NULL");
    printf("Extension: %s\n", extension ? extension : "NULL");
    free(full_path);
    free(full_name);
    
}



void private_dtw_destructor_path(struct DtwPath *self) {
    free(self->first_full_path);
    free(self->dir);
    free(self->name);
    free(self->extension);
    free(self);
}

