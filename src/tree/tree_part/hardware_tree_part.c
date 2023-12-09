





void DtwTreePart_load_content_from_hardware(struct DtwTreePart *self){
    long size;
    bool is_binary;
    char *path = DtwPath_get_path(self->path);

    if(!path){
        return;
    }
    if(dtw_entity_type(path) != DTW_FILE_TYPE){
        return;
    }

    DtwTreePart_free_content(self);
    self->content = dtw_load_any_content(path,&size,&is_binary);
    
    if(!self->content){
        self->content = (unsigned char *)strdup("");
    }    

    self->content_exist_in_memory = true;
    
    self->is_binary = is_binary;
    self->content_size = size;
    self->hardware_content_size = size;
    self->content_exist_in_hardware = true;


}



bool DtwTreePart_hardware_remove(struct DtwTreePart *self, int transaction){
     if(self->ignore == true){
        return false;
     }
     if(transaction == DTW_SET_AS_ACTION){
        self->pending_action = DTW_REMOVE;
        return false;
     }

    char *path =DtwPath_get_path(self->path);

    dtw_remove_any(path);
    
    self->content_exist_in_hardware = false;
    return true;
}

bool DtwTreePart_hardware_write(struct DtwTreePart *self, int transaction){
    if(self->ignore == true){
        return false;
    }
    if(transaction == DTW_SET_AS_ACTION){
        self->pending_action = DTW_WRITE;
        return false;
    }   
    //means that the content not exist in memory
    if(self->content_exist_in_memory == false){
        char *path = DtwPath_get_path(self->path);
        char *dir = DtwPath_get_dir(self->path);
        int entity_type = dtw_entity_type(path);
       
        if(entity_type== DTW_NOT_FOUND && dir!= NULL){
            dtw_create_dir_recursively(dir);
        
        }
 

        return true;
    }
    char *path = DtwPath_get_path(self->path);

    dtw_write_any_content(path,self->content,self->content_size);
    free(self->hawdware_content_sha);
    self->hawdware_content_sha = dtw_generate_sha_from_string((const char  *)self->content);
    self->content_exist_in_hardware = true;
    int now = dtw_get_time();
    self->last_modification_time = now;

    return true;
  
}

bool DtwTreePart_hardware_modify(struct DtwTreePart *self, int transaction){
    if(self->ignore == true){
        return false;
    }
    if(transaction == DTW_SET_AS_ACTION){
        self->pending_action = DTW_MODIFY;
        return false;
    }
    bool changed_path =DtwPath_changed(self->path);

    
    if(changed_path == true && self->content_exist_in_memory == false){
        char *old_path = self->path->original_path;
        char *new_path = DtwPath_get_path(self->path);
        dtw_move_any(old_path,new_path,true);
        return true;
    }
    bool write = false;

    if(changed_path == true && self->content_exist_in_memory == true ){
        char *old_path = self->path->original_path;
        dtw_remove_any(old_path);
        write = true;
    }

    if(changed_path== false && self->content_exist_in_memory == true ){
    
        if(self->metadata_loaded == true){
            char *hardware_sha = self->hawdware_content_sha;
            char *memory_sha = DtwTreePart_get_content_sha(self);
            if(strcmp(hardware_sha,memory_sha) != 0){
                write = true;
            }
        }
        else{
            write = true;
        }
    }

    if(write){
        char *path = DtwPath_get_path(self->path);
        dtw_write_any_content(
            path,
            self->content,
            self->content_size
        );
        free(self->hawdware_content_sha);
        self->hawdware_content_sha = dtw_generate_sha_from_string((const char *)self->content);
        self->content_exist_in_hardware = true;
        int now = dtw_get_time();
        self->last_modification_time = now;

        return true;
    }
    return false;
}

bool DtwTreePart_hardware_commit(struct DtwTreePart *self){
    if(self->ignore == true){
        return false;
    }
    if(self->pending_action == DTW_REMOVE){
        return DtwTreePart_hardware_remove(self,DTW_EXECUTE_NOW);
    }
    if(self->pending_action == DTW_WRITE){
        return DtwTreePart_hardware_write(self,DTW_EXECUTE_NOW);
    }
    if(self->pending_action == DTW_MODIFY){
        return DtwTreePart_hardware_modify(self,DTW_EXECUTE_NOW);
    }
    return false;
}
