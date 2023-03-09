
struct DtwTreePart{
    unsigned int size;
    char *path;
    char *sha256;
    char *content;
    bool ignore_all;
    bool ignore_content;

};

void dtw_set_tree_part_content(struct DtwTreePart *self, char *content){
    self->content = (char*)realloc(self->content,strlen(content) + 1);
    strcpy(self->content,content);
}

void dtw_load_tree_part_content(struct DtwTreePart *self, char *path){
     char *content = dtw_load_file_content(path);
    dtw_set_tree_content(self,content);
    free(content);
}

struct  DtwTreePart * dtw_create_tree(char *path,bool load_content){
    struct DtwTreePart *self = (struct DtwTreePart*)malloc(sizeof(struct DtwTreePart));
    self->size = 0;
    self->path = (char*)malloc(strlen(path) + 1);
    strcpy(self->path, path);
    self->sha256 = (char*)malloc(0);
    self->content = (char*)malloc(0);
    self->ignore_all = false;
    self->ignore_content = false;
    if(load_content){
        dtw_load_tree_part_content(self,path);
    }   
    return self;
}

void dtw_represent_tree_part(struct DtwTreePart *self){
    printf("Path: %s\n", self->path);
    printf("SHA256: %s\n", self->sha256);
    printf("Content: %s\n", self->content);
}

void dtw_free_tree_part(struct DtwTreePart *self){
    free(self->path);
    free(self->sha256);
    free(self->content);
    free(self);
}
