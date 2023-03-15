


struct DtwTreePart * dtw_tree_part_constructor(const char *path,bool load_content,bool preserve_content){
    struct DtwTreePart *self = (struct DtwTreePart *)malloc(sizeof(struct DtwTreePart));
    self->path = dtw_constructor_path(path);
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
    self->copy_tree_part = private_dtw_copy_tree;
    if(load_content){
        
        self->load_content_from_hardware(self);
        if(preserve_content == false){
            self->free_content(self);
        }
    }
    return self;
}

struct  DtwTreePart * private_dtw_copy_tree(struct DtwTreePart *self){
    char *path = self->path->get_path(self->path);

    struct DtwTreePart *new_tree_part = dtw_tree_part_constructor(path,false,false);
    free(path);

    new_tree_part->content_exist_in_memory = self->content_exist_in_memory;
    new_tree_part->content_exist_in_hardware = self->content_exist_in_hardware;
    new_tree_part->is_binary = self->is_binary;
    new_tree_part->ignore = self->ignore;
    new_tree_part->content_size = self->content_size;
    

    new_tree_part->hawdware_content_sha = (char *)malloc(strlen(self->hawdware_content_sha)+1);
    strcpy(new_tree_part->hawdware_content_sha,self->hawdware_content_sha);
    new_tree_part->content = (char *)malloc(self->content_size);
    memcpy(new_tree_part->content,self->content,self->content_size);

    
    return new_tree_part;
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
    char *path = self->path->get_path(self->path);
    if(dtw_entity_type(path) != DTW_FILE_TYPE){
        free(path);
        return;
    }
    self->content = dtw_load_any_content(path,&size,&is_binary);
    self->content_exist_in_memory = true;
    self->is_binary = is_binary;
    self->content_size = size;
    self->last_modification_time = dtw_get_file_last_motification_in_unix(path);
    self->content_exist_in_hardware = true;
    free(self->hawdware_content_sha);
    self->hawdware_content_sha = dtw_generate_sha_from_string(self->content);
    free(path);
    
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
    char *path = self->path->get_path(self->path);
    printf("------------------------------------------------------------\n");
    self->path->represent(self->path);
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
    free(path);

}

bool private_dtw_hardware_remove(struct DtwTreePart *self){
     if(self->ignore == true){
        return false;
     }
    char *path = self->path->get_path(self->path);
    dtw_remove_any(path);
    free(path);
    return true;
}
bool private_dtw_hardware_write(struct DtwTreePart *self){
    if(self->ignore == true){
        return false;
    }
    //means that the content not exist in memory
    if(self->content_exist_in_memory == false){
        char *path = self->path->get_path(self->path);
        char *name = self->path->get_full_name(self->path);
        if(strcmp(name,"") == 0){
            dtw_create_dir_recursively(path);
          
        }
        else{
            dtw_write_string_file_content(path,NULL);
        }
        free(path);
        free(name);
        return true;
    }
    char *path = self->path->get_path(self->path);

    dtw_write_any_content(path,self->content,self->content_size);
    free(path);
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
