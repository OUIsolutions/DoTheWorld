

 DtwPath * newDtwPath(const char *path) {
    struct DtwPath *self = ( DtwPath *)malloc(sizeof(DtwPath));
    *self = (DtwPath){0};

    self->garbage = newDtwStringArray();
    self->dirs = newDtwStringArray();

    if(path){
        DtwPath_set_path(self, path);
        self->original_path_string = strdup(path);
    }

    return self;
}
bool DtwPath_changed( DtwPath *self){

    if(self->original_path_string){
        char *path = DtwPath_get_path(self);
        bool equal =  strcmp(self->original_path_string,path) == 0;
        bool changed = equal == false;
        return changed;
    }

    return true;
}

long DtwPath_get_dirs_size(DtwPath *self){
    return (long)self->dirs->size;
}


char * DtwPath_get_name( DtwPath *self){
    return self->name;

}
char * DtwPath_get_extension(struct DtwPath *self){
    return self->extension;
}

char * DtwPath_get_full_name(struct DtwPath *self){

    const char * name = DtwPath_get_name(self);
    const char * extension = DtwPath_get_extension(self);

    if(name != NULL && extension == NULL){
        return (char*)name;
    }
    if(name == NULL &&extension != NULL){
        return (char*)extension;
    }
    char *value = private_dtw_format("%s.%s",name,extension);
    int possible_index = DtwStringArray_find_position(self->garbage,value);
    if(possible_index != -1){
        free(value);
        return  self->garbage->strings[possible_index];
    }

    DtwStringArray_append(self->garbage,value);
    return value;
}

char * DtwPath_get_dir(struct DtwPath *self){

}

char * DtwPath_get_path(struct DtwPath *self){

}



void DtwPath_set_extension(struct DtwPath *self, const char *extension){
    if(self->extension){
        free(self->extension);
    }
    self->extension == strdup(extension);
}


void DtwPath_set_name(struct DtwPath * self, const char * name){
    if(self->name){
        free(self->name);
    }
    self->name = strdup(self->name);
}

void DtwPath_set_full_name(struct DtwPath * self, const char * full_name){

    if(self->name){
        free(self->name);
        self->name = NULL;
    }
    if(self->extension){
        free(self->extension);
        self->extension = NULL;
    }
    long full_name_size = (long)strlen(full_name);
    for(long i = full_name_size; i >= 0; i--){
        char current_char = full_name[i];
        if(current_char == '.'){
            self->name = private_dtw_sub_str(full_name,0,i);
            self->extension = private_dtw_sub_str(full_name,i,full_name_size);
            return;
        }
    }
    self->name = strdup(full_name);
}


void DtwPath_set_dir(struct DtwPath *self, const char *dir){
    DtwStringArray_free(self->dirs);
    self->dirs = newDtwStringArray();
    long path_size = (long) strlen(dir);

    for(long i = 0; i < path_size; i++){
        char current_char = dir[i];

    }
}

void DtwPath_set_path(struct DtwPath *self, const char *target_path) {

}

void DtwPath_add_start_dir(struct DtwPath *self, const char *start_dir){

}

void DtwPath_add_end_dir(struct DtwPath *self, const char *end_dir){

}

  

void DtwPath_represent(struct DtwPath *self){
    char  *path = DtwPath_get_path(self);
    char *full_name = DtwPath_get_full_name(self);
    char *dir = DtwPath_get_dir(self);
    char *name = DtwPath_get_name(self);
    char *extension = DtwPath_get_extension(self);
    bool changed = DtwPath_changed(self);

    printf("First Path: %s\n", self->original_path_string ? self->original_path_string : "NULL");
    printf("Path: %s\n", path  ? path : "NULL");
    printf("Path Changed: %s\n", changed ? "true" : "false");
    printf("Dir: %s\n", dir ? dir : "NULL");
    printf("Full Name: %s\n", full_name ? full_name : "NULL");
    printf("Name: %s\n", name ? name : "NULL");
    printf("Extension: %s\n", extension ? extension : "NULL");

}



void DtwPath_free(struct DtwPath *self) {
    DtwStringArray_free(self->garbage);
    DtwStringArray_free(self->dirs);

    if(self->name){
        free(self->name);
    }

    if(self->extension){
        free(self->extension);
    }

    free(self);
}

