


struct DtwTreePart * newDtwTreePart(const char *path, DtwTreeProps *props){
    DtwTreeProps formated_props = DtwTreeProps_format_props(props);

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


    if(formated_props.content == DTW_INCLUDE || formated_props.hadware_data == DTW_INCLUDE){
        
        DtwTreePart_load_content_from_hardware(self);
        if(formated_props.hadware_data == DTW_INCLUDE && self->content_exist_in_memory){

            self->metadata_loaded = true;
            self->last_modification_time = dtw_get_file_last_motification_in_unix(path);
            free(self->hawdware_content_sha);
            self->hawdware_content_sha = dtw_generate_sha_from_string((const char*)self->content);
        }

        if(formated_props.content == DTW_HIDE){
            DtwTreePart_free_content(self);
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
    char *path = DtwPath_get_path(self->path);
    DtwTreeProps props = {.content =DTW_NOT_LOAD,.hadware_data = DTW_NOT_LOAD};
    DtwTreePart *new_tree_part = newDtwTreePart(
            path,
            &props
    );
    free(path);

    new_tree_part->content_exist_in_memory = self->content_exist_in_memory;
    new_tree_part->content_exist_in_hardware = self->content_exist_in_hardware;
    new_tree_part->is_binary = self->is_binary;
    new_tree_part->ignore = self->ignore;
    new_tree_part->content_size = self->content_size;

    char * possible_sha = DtwTreePart_get_content_sha(self);

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

    DtwTreePart_free_content(self);
    self->content_exist_in_memory = true;
    self->is_binary = is_binary;
    self->content = (unsigned char *)realloc(self->content,content_size+2);
    memcpy(self->content,content,content_size);
    self->content_size = content_size;


}

void DtwTreePart_set_string_content(struct DtwTreePart *self, const char *content){
    DtwTreePart_set_any_content(
        self,
        (unsigned char*)content,
        strlen(content),
        false
    );
    
    self->content[self->content_size] = '\0';
}

void DtwTreePart_set_binary_content(struct DtwTreePart *self, unsigned char *content, int content_size){
    DtwTreePart_set_any_content(self,content,content_size,true);
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



void DtwTreePart_represent(struct DtwTreePart *self){
    char *path = DtwPath_get_path(self->path);
    printf("------------------------------------------------------------\n");
    DtwPath_represent(self->path);
    printf("Content Exist in Memory: %s\n",self->content_exist_in_memory ? "true" : "false");
    printf("Ignore: %s\n",self->ignore ? "true" : "false");

    printf("Content Exist In Hardware: %s\n",self->content_exist_in_hardware ? "true" : "false");
    printf("Is Binary: %s\n",self->is_binary ? "true" : "false");

    if(self->last_modification_time){
        printf("Last Modification Time in Unix: %li\n",self->last_modification_time);
        char *last_moditication_in_string = DtwTreePart_last_modification_time_in_string(self);
        printf("Last Modification Time: %s\n",last_moditication_in_string);
        free(last_moditication_in_string);
    }

    printf("Content Size: %li\n",self->content_size);

    char *content_sha = DtwTreePart_get_content_sha(self);
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
    DtwPath_free(self->path);
    free(self->hawdware_content_sha);
    free(self->content);
    free(self);
}

struct DtwTreePart * newDtwTreePartEmpty(const char *path){
    DtwTreeProps  props = {.content =DTW_NOT_LOAD,.hadware_data = DTW_NOT_LOAD};
    return newDtwTreePart(
            path,
         &props
    );

}


struct DtwTreePart * newDtwTreePartLoading(const char *path){
    DtwTreeProps  props = {.content =DTW_LOAD,.hadware_data = DTW_LOAD};
    return newDtwTreePart(
            path,
            &props
    );
}
