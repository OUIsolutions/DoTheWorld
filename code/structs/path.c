
struct DtwPath {
    char *first_full_path;
    char *dir;
    char *name;
    char *extension;

    //Getters
    bool  (*changed)(struct DtwPath *self);
    char *(*get_full_name) (struct DtwPath *self);
    char *(*get_name) (struct DtwPath *self);
    char *(*get_extension) (struct DtwPath *self);

    char *(*get_full_path) (struct DtwPath *self);
    char *(*get_dir) (struct DtwPath *self);

    
    //Setters
    void (*set_extension) (struct DtwPath *self, const char *extension);
    void (*set_name) (struct DtwPath *self, const char *name);
    void (*set_dir) (struct DtwPath *self, const char *path);
    void (*set_full_name) (struct DtwPath *self, const char *full_name);
    void (*set_full_path) (struct DtwPath *self, const char *full_path);
    void (*represent)(struct DtwPath *self);
    void (*delete) (struct DtwPath *self);


};
bool  private_dtw_path_changed(struct DtwPath *self);
char *private_dtw_get_full_name(struct DtwPath *self);
char *private_dtw_get_name(struct DtwPath *self);
char *private_dtw_get_extension(struct DtwPath *self);
char *private_dtw_get_full_path(struct DtwPath *self);
char *private_dtw_get_dir(struct DtwPath *self);

void private_dtw_set_extension(struct DtwPath *self, const char *extension);
void private_dtw_set_name(struct DtwPath * self, const char * name);
void private_dtw_set_dir(struct DtwPath *self, const char *path);

void private_dtw_set_full_name(struct DtwPath * self, const char * full_name);
void private_dtw_set_full_path(struct DtwPath *self, const char *ful_path);

void private_dtw_represent_path(struct DtwPath *self);
void private_dtw_destructor_path(struct DtwPath *self);


struct DtwPath * dtw_constructor_path( const char *ful_path) {
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
    self->delete = private_dtw_destructor_path;

    self->set_full_path(self, ful_path);
    self->first_full_path = self->get_full_path(self);

    return self;
}
bool private_dtw_path_changed(struct DtwPath *self){
    if(strcmp(self->first_full_path, self->get_full_path(self)) == 0){
        return false;
    }
    return true;
}

char * private_dtw_get_full_name(struct DtwPath *self){
    char *full_name = (char *)malloc(strlen(self->name) + strlen(self->extension) +1);
    //concat the name and extension with / 
    //if the extension is empty, then the full name is just the name
    if(strcmp(self->extension, "") == 0){
        sprintf(full_name, "%s", self->name);
    }else{
        sprintf(full_name, "%s.%s", self->name, self->extension);
    }
    return full_name;
}
char * private_dtw_get_name(struct DtwPath *self){
    return self->name;
}
char * private_dtw_get_extension(struct DtwPath *self){
    return self->extension;
}


char * private_dtw_get_full_path(struct DtwPath *self){
    char *full_path = (char *)malloc(strlen(self->dir) + strlen(self->name) + strlen(self->extension) +3);
    //concat the path, name and extension with / 
    char *full_name = self->get_full_name(self);
    //if the dir is empty, then the full path is just the full name
    if(strcmp(self->dir, "") == 0){
        sprintf(full_path, "%s", full_name);
    }else{
        sprintf(full_path, "%s/%s", self->dir, full_name);
    }
    free(full_name);
    return full_path;
}

char * private_dtw_get_dir(struct DtwPath *self){
    return self->dir;
}


void private_dtw_set_extension(struct DtwPath *self, const char *extension){

    self->extension = (char *)realloc(self->extension, strlen(extension));
    strcpy(self->extension, extension);
}


void private_dtw_set_name(struct DtwPath * self, const char * name){

    self->name = (char *)realloc(self->name, strlen(name));
    strcpy(self->name, name);
}

void private_dtw_set_dir(struct DtwPath *self, const char *path){

    self->dir = (char *)realloc(self->dir, strlen(path));
    strcpy(self->dir, path);
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
    //means there is no .
    self->set_name(self, full_name);

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
    printf("Full Path: %s\n", self->get_full_path(self));
    printf("Changed: %s\n", self->changed(self) ? "true" : "false");
    printf("Dir: %s\n", self->get_dir(self));
    printf("Full Name: %s\n", self->get_full_name(self));
    printf("Name: %s\n", self->get_name(self));
    printf("Extension: %s\n", self->get_extension(self));
}



void private_dtw_destructor_path(struct DtwPath *self) {
    free(self->first_full_path);
    free(self->dir);
    free(self->name);
    free(self->extension);
    free(self);
}

