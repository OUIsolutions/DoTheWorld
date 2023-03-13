
struct DtwTreePart{
    struct DtwPath *path;
    bool content_exist;
    bool content_exist_in_hardware;
    bool is_binary;
    char *hawdwere_sha;
    char *content;
    int content_size;
    void (*set_any_content)(struct DtwTreePart *self,const char *content,int content_size,bool is_binary);
    void (*set_string_content)(struct DtwTreePart *self,const char *content);
    void (*set_binary_content)(struct DtwTreePart *self,const char *content,int content_size);
    void (*load_content_from_hardware)(struct DtwTreePart *self);
    void (*delete)(struct DtwTreePart *self);
};
void private_dtw_set_any_content(struct DtwTreePart *self,const char *content,int content_size,bool is_binary);
void private_dtw_set_string_content(struct DtwTreePart *self,const char *content);
void private_dtw_set_binary_content(struct DtwTreePart *self,const char *content,int content_size);
void private_dtw_load_content_from_hardware(struct DtwTreePart *self);
void private_dtw_tree_part_destructor(struct DtwTreePart *self);


struct DtwTreePart * dtw_tree_part_constructor(const char *full_path,bool load_content){
    struct DtwTreePart *self = (struct DtwTreePart *)malloc(sizeof(struct DtwTreePart));
    self->path = dtw_constructor_path(full_path);
    self->content_exist = false;
    self->content_exist_in_hardware = false;
    self->is_binary = false;
    self->hawdwere_sha = (char *)malloc(0);
    self->content = (char *)malloc(0);
    self->content_size = 0;
    self->load_content_from_hardware = private_dtw_load_content_from_hardware;
    self->set_any_content = private_dtw_set_any_content;
    self->set_string_content = private_dtw_set_string_content;
    self->set_binary_content = private_dtw_set_binary_content;

    self->delete = private_dtw_tree_part_destructor;
    return self;
}


void private_dtw_set_any_content(struct DtwTreePart *self,const char *content,int content_size,bool is_binary){
    self->content_exist = true;
    self->is_binary = is_binary;
    self->content = (char *)realloc(self->content,content_size);
    memcpy(self->content,content,content_size);
    self->content_size = content_size;
}

void private_dtw_set_string_content(struct DtwTreePart *self,const char *content){
    self->set_any_content(self,content,strlen(content),false);
}
void private_dtw_set_binary_content(struct DtwTreePart *self,const char *content,int content_size){
    self->set_any_content(self,content,content_size,true);
}

void private_dtw_load_content_from_hardware(struct DtwTreePart *self){
    
}


void private_dtw_tree_part_destructor(struct DtwTreePart *self){
    self->path->delete(self->path);
    free(self->hawdwere_sha);
    free(self->content);
    free(self);
}
