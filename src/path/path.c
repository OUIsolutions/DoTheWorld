

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
            start = i+1;
            break;
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
            start = i+1;
            break;
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
            start = i+1;
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
            end = i+1;
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

    long path_size = (long)strlen(self->path);
    long end = -1;
    for(long i = path_size-1; i >=0; i--){
        char current_char = self->path[i];
        if(current_char == '.'){
            end = i;
            break;
        }
    }

    char *without_extension = NULL;
    if(end != -1){
        without_extension = private_dtw_sub_str(self->path,0,end);
    }
    else{
        without_extension = self->path;
    }
    char *formated_extension = dtw_replace_string(extension,".","");
    char *buffer = private_dtw_formatt("%s.%s",without_extension,formated_extension);
    if(end != -1){
        free(without_extension);
    }

    free(self->path);
    free(formated_extension);
    self->path = buffer;

}


void DtwPath_set_name(struct DtwPath * self, const char * name){

}



void DtwPath_set_full_name(struct DtwPath * self, const char * full_name){

}


void DtwPath_set_dir(struct DtwPath *self, const char *path){

}

void DtwPath_set_path(struct DtwPath *self, const char *target_path) {
    free(self->path);
    self->path = private_dtw_format_path(target_path);
}

void DtwPath_add_start_dir(struct DtwPath *self, const char *start_dir){

    char *element = self->
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
    free(self->original_path_string);
    free(self->path);
    free(self);
}

