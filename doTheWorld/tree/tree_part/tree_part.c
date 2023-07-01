


struct DtwTreePart * newDtwTreePart(const char *path, bool load_content, bool load_meta_data){
    struct DtwTreePart *self = (struct DtwTreePart *)malloc(sizeof(struct DtwTreePart));
    self->path = newDtwPath(path);
    self->content_exist_in_memory = false;
    self->content_exist_in_hardware = false;
    self->last_modification_time = 0;
    self->is_binary = false;
    self->ignore = false;
    self->metadata_loaded = false;
    self->pending_action = 0;
    self->hawdware_content_sha = (char *)malloc(0);
    self->content = (unsigned char *)malloc(0);
    self->content_size = 0;
    self->hardware_content_size = 0;


    self->get_content_string_by_reference = DtwTreePart_get_content_string_by_reference;
    self->get_content_binary_by_reference = DtwTreePart_get_content_binary_by_reference;
    self->load_content_from_hardware = DtwTreePart_load_content_from_hardware;
    self->set_any_content = DtwTreePart_set_any_content;
    self->set_string_content = DtwTreePart_set_string_content;
    self->set_binary_content = DtwTreePart_set_binary_content;
    self->get_content_sha = DtwTreePart_get_content_sha;
    self->last_modification_time_in_string = DtwTreePart_last_modification_time_in_string;
    self->free_content = DtwTreePart_free_content;
    self->represent = DtwTreePart_represent_tree_part;
    self->hardware_remove = DtwTreePart_hardware_remove;
    self->hardware_write = DtwTreePart_hardware_write;
    self->hardware_modify = DtwTreePart_hardware_modify;
    self->hardware_commit = DtwTreePart_hardware_commit;
    self->free = DtwTreePart_free;
    self->self_copy = DtwTreePart_self_copy;

    if(load_content || load_meta_data){
        
        self->load_content_from_hardware(self);
        if(load_meta_data && self->content_exist_in_memory){

            self->metadata_loaded = true;
            self->last_modification_time = dtw_get_file_last_motification_in_unix(path);
            free(self->hawdware_content_sha);
            self->hawdware_content_sha = dtw_generate_sha_from_string((const char*)self->content);
        }

        if(!load_content){
            self->free_content(self);
        }
    }

    return self;
}
char *DtwTreePart_get_content_string_by_reference(struct DtwTreePart *self){
    if(self->content_exist_in_memory == true){
        return (char *)self->content;
    }
    return NULL;
}

unsigned char *DtwTreePart_get_content_binary_by_reference(struct DtwTreePart *self){
    if(self->content_exist_in_memory == true){
        return self->content;
    }
    return NULL;
}


struct  DtwTreePart * DtwTreePart_self_copy(struct DtwTreePart *self){
    char *path = self->path->get_path(self->path);

    DtwTreePart *new_tree_part = newDtwTreePart(path, false, false);
    free(path);

    new_tree_part->content_exist_in_memory = self->content_exist_in_memory;
    new_tree_part->content_exist_in_hardware = self->content_exist_in_hardware;
    new_tree_part->is_binary = self->is_binary;
    new_tree_part->ignore = self->ignore;
    new_tree_part->content_size = self->content_size;

    char * possible_sha = self->get_content_sha(self);

    if(possible_sha){
        free(new_tree_part->hawdware_content_sha);
        new_tree_part->hawdware_content_sha = possible_sha;
    }


    free(new_tree_part->content);
    new_tree_part->content = (unsigned char *)malloc(self->content_size + 2);
    
    if(new_tree_part->is_binary == false){
            new_tree_part->content[self->content_size] = '\0';    
    }
    
    memcpy(new_tree_part->content,self->content,self->content_size);

    
    return new_tree_part;
}

void DtwTreePart_set_any_content(struct DtwTreePart *self, unsigned char *content, int content_size, bool is_binary){

    self->free_content(self);
    self->content_exist_in_memory = true;
    self->is_binary = is_binary;
    self->content = (unsigned char *)realloc(self->content,content_size+2);
    memcpy(self->content,content,content_size);
    self->content_size = content_size;


}

void DtwTreePart_set_string_content(struct DtwTreePart *self, const char *content){
    self->set_any_content(
        self,
        (unsigned char*)content,
        strlen(content),
        false
    );
    
    self->content[self->content_size] = '\0';
}

void DtwTreePart_set_binary_content(struct DtwTreePart *self, unsigned char *content, int content_size){
    self->set_any_content(self,content,content_size,true);
}


char *DtwTreePart_get_content_sha(struct DtwTreePart *self){
    if(self->content_exist_in_memory){
        return dtw_generate_sha_from_string((char *)self->content);
    }
    return NULL;
}

char *DtwTreePart_last_modification_time_in_string(struct DtwTreePart *self){
    return dtw_convert_unix_time_to_string(self->last_modification_time);
}



void DtwTreePart_represent_tree_part(struct DtwTreePart *self){
    char *path = self->path->get_path(self->path);
    printf("------------------------------------------------------------\n");
    self->path->represent(self->path);
    printf("Content Exist in Memory: %s\n",self->content_exist_in_memory ? "true" : "false");
    printf("Ignore: %s\n",self->ignore ? "true" : "false");

    printf("Content Exist In Hardware: %s\n",self->content_exist_in_hardware ? "true" : "false");
    printf("Is Binary: %s\n",self->is_binary ? "true" : "false");

    if(self->last_modification_time){
        printf("Last Modification Time in Unix: %li\n",self->last_modification_time);
        char *last_moditication_in_string = self->last_modification_time_in_string(self);
        printf("Last Modification Time: %s\n",last_moditication_in_string);
        free(last_moditication_in_string);
    }

    printf("Content Size: %li\n",self->content_size);

    char *content_sha = self->get_content_sha(self);
    if(content_sha){
        printf("Content SHA:  %s\n",content_sha);
        free(content_sha);
    }
    if(self->content_exist_in_memory && self->is_binary == false){
        printf ("Content: %s\n",self->content);
    }
    if(self->is_binary == true){
        printf("Content: Binary\n");
    }
    
    const char *action = private_dtw_convert_action_to_string(self->pending_action);
    if(action){
        printf("Pending Action: %s\n",action);

    }
    free(path);

}


void DtwTreePart_free_content(struct DtwTreePart *self){
    self->content_exist_in_memory = false;
    self->content = (unsigned char *)realloc(self->content,0);
}
void DtwTreePart_free(struct DtwTreePart *self){
    self->path->free(self->path);
    free(self->hawdware_content_sha);
    free(self->content);
    free(self);
}
