
struct DtwTreePart{
    char *path;

    unsigned char *content;
    unsigned int last_modification_in_unix;
    unsigned int size;
    bool binary;
    bool ignore;
};

void dtw_set_tree_part_any_content(struct DtwTreePart *self, char *content, int size, bool is_binary, bool last_modification_in_unix){
    // copy content
    self->content = (char *)realloc(self->content, strlen(content) + 1);
    strcpy(self->content, content);
    // calc sha25
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


void dtw_set_tree_part_binary_content(struct DtwTreePart *self, char *content, int size, bool last_modification_in_unix){
    dtw_set_tree_part_any_content(self, content, size, true, last_modification_in_unix);
}


void dtw_set_tree_part_string_content(struct DtwTreePart *self, char *content, bool last_modification_in_unix){
    dtw_set_tree_part_any_content(self, content, strlen(content), false, last_modification_in_unix);
}


void dtw_implement_tree_part(struct DtwTreePart *self){
    if(self->ignore){
        return;
    }
    dtw_write_any_content(self->path, self->content, self->size,true);
}


struct DtwTreePart *dtw_create_tree_part(char *path, bool load_content){
    struct DtwTreePart *self = (struct DtwTreePart *)malloc(sizeof(struct DtwTreePart));
    self->size = 0;

    self->content = (char *)malloc(0);
    self->last_modification_in_unix = 0;
    self->size = 0;
    self->binary = false;
    self->ignore = false;
    self->path = (char *)malloc(strlen(path) + 1);
    strcpy(self->path, path);

    if (load_content){
        int size;
        bool is_binary;
        char *content = dtw_load_any_content(path, &size, &is_binary);
        if (content != NULL){
            // get last modification time
            struct stat attr;
            stat(path, &attr);
            int last_modification_in_unix = attr.st_mtime;
            dtw_set_tree_part_any_content(self, content, size, is_binary, last_modification_in_unix);
            free(content);
        }
    }
    return self;
}


void dtw_represent_tree_part(struct DtwTreePart *self){
    printf("-------------------------------------------\n");
    printf("Path: %s\n", self->path);
    printf("Size: %d\n", self->size);
    printf("Binary: %s\n", self->binary ? "true" : "false");
    // convert time to human readable
    time_t t = self->last_modification_in_unix;
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);
    printf("Last modification: %s\n", s);

    printf("Content:\n%s\n", self->content);
}

void dtw_free_tree_part(struct DtwTreePart *self){
    free(self->path);
    free(self->content);
    free(self);
}
