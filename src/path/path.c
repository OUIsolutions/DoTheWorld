

struct DtwPath * newDtwPath(const char *path) {
    struct DtwPath *self = (struct DtwPath *)malloc(sizeof(struct DtwPath));
    self->garbage = newDtwStringArray();
    self->path = private_dtw_format_path(path);
    self->original_path_string = strdup(self->path);


    return self;
}
bool DtwPath_changed(struct DtwPath *self){
    return strcmp(self->path,self->original_path_string) != 0;
}


char * DtwPath_get_name(struct DtwPath *self){

    long path_size = (long)strlen(self->path);
    long start = 0;
    long end = path_size;
    for(long i = path_size-1; i >=0; i--){
        char current_char = self->path[i];
        if(current_char == '/' || current_char == '\\'){
            start = i;
        }
        if(current_char == '.'){
            end = i;
        }
    }
    if(end - start == 0){
        return NULL;
    }

    char *buffer = private_dtw_sub_str(self->path,start,end);
    return privateDtwStringArray_append_if_not_included(self->garbage,buffer);

}
char * DtwPath_get_extension(struct DtwPath *self){
    long path_size = (long)strlen(self->path);
    long start = -1;
    long end = path_size;
    for(long i = path_size-1; i >=0; i--){
        char current_char = self->path[i];
        if(current_char == '.'){
            start = i;
        }
    }
    if(start == -1){
        return  NULL;
    }
    char *buffer = private_dtw_sub_str(self->path,start,end);
    return privateDtwStringArray_append_if_not_included(self->garbage,buffer);
}

char * DtwPath_get_full_name(struct DtwPath *self){
    long path_size = (long)strlen(self->path);
    long start = 0;
    long end = path_size;
    for(long i = path_size-1; i >=0; i--){
        char current_char = self->path[i];
        if(current_char == '/' || current_char == '\\'){
            start = i;
            break;
        }
    }
    if(end - start == 0){
        return NULL;
    }
    char *buffer = private_dtw_sub_str(self->path,start,end);
    return privateDtwStringArray_append_if_not_included(self->garbage,buffer);
}

char * DtwPath_get_dir(struct DtwPath *self){
    long path_size = (long)strlen(self->path);
    long start = 0;
    long end = -1;
    for(long i = path_size-1; i >=0; i--){
        char current_char = self->path[i];
        if(current_char == '/' || current_char == '\\'){
            end = i;
            break;
        }
    }
    if(end == -1){
        return NULL;
    }

    char *buffer = private_dtw_sub_str(self->path,start,end);
    return privateDtwStringArray_append_if_not_included(self->garbage,buffer);
}

char * DtwPath_get_path(struct DtwPath *self){
    return self->path;
}



void DtwPath_set_extension(struct DtwPath *self, const char *extension){



}


void DtwPath_set_name(struct DtwPath * self, const char * name){

}



void DtwPath_set_full_name(struct DtwPath * self, const char * full_name){

}


void DtwPath_set_dir(struct DtwPath *self, const char *path){

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
    free(self->dir);
    free(self->name);
    free(self->extension);
    free(self);
}

