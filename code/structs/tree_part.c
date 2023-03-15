
struct DtwTreePart{
    
    struct DtwPath *path;
    bool content_exist_in_memory;
    long last_modification_time;
    bool content_exist_in_hardware;
    bool ignore;
    bool is_binary;
    char *hawdware_content_sha;
    char *content;

    int content_size;
    char *(*get_content_sha)(struct DtwTreePart *self);
    char *(*last_modification_time_in_string)(struct DtwTreePart *self);
    void (*set_any_content)(struct DtwTreePart *self,const char *content,int content_size,bool is_binary,bool set_last_modification_time);
    void (*set_string_content)(struct DtwTreePart *self,const char *content);
    void (*set_binary_content)(struct DtwTreePart *self,const char *content,int content_size);
    void (*load_content_from_hardware)(struct DtwTreePart *self);
    void (*free_content)(struct DtwTreePart *self);
    void(*represent)(struct DtwTreePart *self);
    bool(*hardware_remove)(struct DtwTreePart *self);
    bool(*hardware_write)(struct DtwTreePart *self);
    void (*delete_tree_part)(struct DtwTreePart *self);
};
char *private_dtw_get_content_sha(struct DtwTreePart *self);
char *private_dtw_last_modification_time_in_string(struct DtwTreePart *self);
void private_dtw_set_any_content(struct DtwTreePart *self,const char *content,int content_size,bool is_binary,bool set_last_modification_time);
void private_dtw_set_string_content(struct DtwTreePart *self,const char *content);
void private_dtw_set_binary_content(struct DtwTreePart *self,const char *content,int content_size);
void private_dtw_load_content_from_hardware(struct DtwTreePart *self);
void private_dtw_free_content(struct DtwTreePart *self);
void private_dtw_represent_tree_part(struct DtwTreePart *self);
bool private_dtw_hardware_remove(struct DtwTreePart *self);
bool private_dtw_hardware_write(struct DtwTreePart *self);
void private_dtw_tree_part_destructor(struct DtwTreePart *self);


struct DtwTreePart * dtw_tree_part_constructor(const char *full_path,bool load_content){
    struct DtwTreePart *self = (struct DtwTreePart *)malloc(sizeof(struct DtwTreePart));
    self->path = dtw_constructor_path(full_path);
    self->content_exist_in_memory = false;
    self->content_exist_in_hardware = false;
    self->is_binary = false;
    self->ignore = false;
    self->hawdware_content_sha = (char *)malloc(0);
    self->content = (char *)malloc(0);
    self->content_size = 0;
    self->load_content_from_hardware = private_dtw_load_content_from_hardware;
    self->set_any_content = private_dtw_set_any_content;
    self->set_string_content = private_dtw_set_string_content;
    self->set_binary_content = private_dtw_set_binary_content;
    self->get_content_sha = private_dtw_get_content_sha;
    self->last_modification_time_in_string = private_dtw_last_modification_time_in_string;
    self->free_content = private_dtw_free_content;
    self->represent = private_dtw_represent_tree_part;
    self->hardware_remove = private_dtw_hardware_remove;
    self->hardware_write = private_dtw_hardware_write;
    self->delete_tree_part = private_dtw_tree_part_destructor;

    if(load_content){
        self->load_content_from_hardware(self);
    }
    return self;
}


void private_dtw_set_any_content(struct DtwTreePart *self,const char *content,int content_size,bool is_binary,bool set_last_modification_time){
    self->free_content(self);
    self->content_exist_in_memory = true;
    self->is_binary = is_binary;
    self->content = (char *)realloc(self->content,content_size);
    memcpy(self->content,content,content_size);
    self->content_size = content_size;

    if(set_last_modification_time){
        self->last_modification_time = time(NULL);
    }
}

void private_dtw_set_string_content(struct DtwTreePart *self,const char *content){
    self->set_any_content(self,content,strlen(content),false,true);
    self->content[self->content_size] = '\0';
}
void private_dtw_set_binary_content(struct DtwTreePart *self,const char *content,int content_size){
    self->set_any_content(self,content,content_size,true,true);
}

void private_dtw_load_content_from_hardware(struct DtwTreePart *self){
    int size;
    bool is_binary;
    char *full_path = self->path->get_full_path(self->path);
    if(dtw_entity_type(full_path) != DTW_FILE_TYPE){
        free(full_path);
        return;
    }
    self->content = dtw_load_any_content(full_path,&size,&is_binary);
    self->content_exist_in_memory = true;
    self->is_binary = is_binary;
    self->content_size = size;
    self->last_modification_time = dtw_get_file_last_motification_in_unix(full_path);
    self->content_exist_in_hardware = true;
    free(self->hawdware_content_sha);
    self->hawdware_content_sha = dtw_generate_sha_from_string(self->content);
    free(full_path);
    
}
char *private_dtw_get_content_sha(struct DtwTreePart *self){
    if(self->content_exist_in_memory){
        return dtw_generate_sha_from_string(self->content);
    }
    return NULL;
}

char *private_dtw_last_modification_time_in_string(struct DtwTreePart *self){
    return dtw_convert_unix_time_to_string(self->last_modification_time);
}



void private_dtw_represent_tree_part(struct DtwTreePart *self){
    char *full_path = self->path->get_full_path(self->path);
    printf("------------------------------------------------------------\n");
    printf("Path: %s\n",full_path);
    printf("Content Exist in Memory: %s\n",self->content_exist_in_memory ? "true" : "false");
    if(self->content_exist_in_memory == true || self->content_exist_in_hardware == true){
        
        char *last_moditication_in_string = self->last_modification_time_in_string(self);

        printf("Content Exist In Hardware: %s\n",self->content_exist_in_hardware ? "true" : "false");
        printf("Is Binary: %s\n",self->is_binary ? "true" : "false");
        printf("Last Modification Time in Unix: %li\n",self->last_modification_time);
        printf("Last Modification Time: %s\n",last_moditication_in_string);
        printf("Content Size: %d\n",self->content_size);
        printf("Hardware SHA: %s\n",self->hawdware_content_sha);    
        if(self->content_exist_in_memory == true){
            char *content_sha = self->get_content_sha(self);
            printf("Content SHA:  %s\n",content_sha);
            printf ("Content: %s\n",self->content);
            free(content_sha);
        }
        
        free(last_moditication_in_string);
    }
    free(full_path);

}

bool private_dtw_hardware_remove(struct DtwTreePart *self){
     if(self->ignore == true){
        return false;
     }
    char *full_path = self->path->get_full_path(self->path);
    dtw_remove_any(full_path);
    free(full_path);
    return true;
}
bool private_dtw_hardware_write(struct DtwTreePart *self){
    if(self->ignore == true){
        return false;
    }
    //means that the content not exist in memory
    if(self->content_exist_in_memory == false){
        char *full_path = self->path->get_full_path(self->path);
        char *name = self->path->get_full_name(self->path);
        if(strcmp(name,"") == 0){
            dtw_create_dir_recursively(full_path);
          
        }
        else{
            dtw_write_string_file_content(full_path,NULL);
        }
        free(full_path);
        free(name);
        return true;
    }
    char *full_path = self->path->get_full_path(self->path);

    dtw_write_any_content(full_path,self->content,self->content_size);
    free(full_path);
    return true;
  
}

void private_dtw_free_content(struct DtwTreePart *self){
    self->content_exist_in_memory = false;
    self->content = (char *)realloc(self->content,0);
}
void private_dtw_tree_part_destructor(struct DtwTreePart *self){
    self->path->delete_path(self->path);
    free(self->hawdware_content_sha);
    free(self->content);
    free(self);
}
