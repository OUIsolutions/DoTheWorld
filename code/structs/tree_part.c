
struct DtwTreePart{
    char *full_path;
    char *path;
    char *full_name;
    char *name;
    char *extension;
    char *content;
    char *sha_256;
    unsigned int last_modification_in_unix;
    unsigned int size;
    bool binary;
    bool ignore;
};
//Declaration
void dtw_set_tree_part_path(struct DtwTreePart *self,const char *path);
void dtw_load_tree_part_content_from_file(struct DtwTreePart *self,const char *path,bool set_sha_256);
void dtw_set_tree_part_any_content(struct DtwTreePart *self,char *content,int size,bool is_binary,int last_modification_in_unix,bool set_sha_256);



struct DtwTreePart *dtw_create_tree_part(const char *path, bool load_content, bool set_sha_256){
    struct DtwTreePart *self = (struct DtwTreePart *)malloc(sizeof(struct DtwTreePart));
    
    self->full_path = (char *)malloc(1);

    self->size = 0;
    self->last_modification_in_unix = 0;
    self->size = 0;
    self->binary = false;
    self->ignore = false;
    dtw_set_tree_part_path(self,path);
    if (load_content){
        dtw_load_tree_part_content_from_file(self,path, set_sha_256);
    }
    return self;
}


void dtw_set_tree_part_path(struct DtwTreePart *self,const char *path){
    free(self->full_path);
    self->full_path = (char *)malloc(strlen(path) + 1);
    strcpy(self->full_path, path);
}

void dtw_load_tree_part_content_from_file(struct DtwTreePart *self,const char *path,bool set_sha_256){
        int size;
        bool is_binary;
        free(self->content);
        char *content = dtw_load_any_content(path, &size, &is_binary);
        if (content != NULL){
            // get last modification time
            int last_modification_in_unix = dtw_get_file_last_motification_in_unix(path);
           
            dtw_set_tree_part_any_content(
                self,
                content,
                size,
                is_binary,
                last_modification_in_unix,
                set_sha_256
                );
            free(content);
        }
}

void dtw_set_tree_part_any_content(
    struct DtwTreePart *self,
    char *content,
    int size,
    bool is_binary,
    int last_modification_in_unix,
    bool set_sha_256
    ){
    // copy content
    free(self->content);
    self->content = (char *)malloc(size + 1);
    strcpy(self->content, content);
    // calc sha25
    if (set_sha_256){
        free(self->sha_256);
        self->sha_256 = dtw_generate_sha_from_string(content);
    }
    if (size == 0){
        self->size = strlen(content);
    }
    else{
        self->size = size;
    }

    if (last_modification_in_unix == 0){
        // set time as now
        time_t now = time(NULL);
        self->last_modification_in_unix = now;
    }
    else{
        self->last_modification_in_unix = last_modification_in_unix;
    }
}


void dtw_set_tree_part_binary_content(
    struct DtwTreePart *self, 
    char *content, 
    int size,
    int last_modification_in_unix,
    bool set_sha_256
    ){
    dtw_set_tree_part_any_content(self, content, size, true, last_modification_in_unix,set_sha_256);
}


void dtw_set_tree_part_string_content(
    struct DtwTreePart *self,
    char *content,
    int last_modification_in_unix,
    bool set_sha_256){
    dtw_set_tree_part_any_content(self, content, strlen(content), false, last_modification_in_unix,set_sha_256);
}


void dtw_implement_tree_part(struct DtwTreePart *self){
    if(self->ignore){
        return;
    }
    dtw_write_any_content(self->full_path, self->content, self->size,true);
}




void dtw_represent_tree_part(struct DtwTreePart *self){
    char * last_modification = dtw_convert_unix_time_to_string(self->last_modification_in_unix);

    printf("-------------------------------------------\n");
    printf("Full Path: %s\n", self->full_path);

    printf("Size: %d\n", self->size);
    printf("Binary: %s\n", self->binary ? "true" : "false");
    printf("Ignore: %s\n", self->ignore ? "true" : "false");
    printf("SHA-256: %s\n", self->sha_256);
    printf("Last modification in unix: %d\n", self->last_modification_in_unix);
    printf("Last modification: %s\n", last_modification);
    free(last_modification);
    printf("Content:\n%s\n", self->content);
}



void dtw_free_tree_part(struct DtwTreePart *self){
    free(self->full_path);

    free(self->sha_256);
    free(self->content);
    free(self);
}
