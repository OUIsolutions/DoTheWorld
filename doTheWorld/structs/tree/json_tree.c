



void private_dtw_loads_json_tree(struct DtwTree *self,const char *content){
    //load json
    cJSON *json_tree = cJSON_Parse(content);
    int size = cJSON_GetArraySize(json_tree);
    for(int i = 0; i < size; i++){

        cJSON *json_tree_part = cJSON_GetArrayItem(json_tree, i);
        cJSON *path = cJSON_GetObjectItemCaseSensitive(json_tree_part, "path");
        cJSON *original_path = cJSON_GetObjectItemCaseSensitive(json_tree_part, "original_path");
        cJSON *hardware_sha = cJSON_GetObjectItemCaseSensitive(json_tree_part, "hardware_sha256");
        cJSON *hardware_content_size = cJSON_GetObjectItemCaseSensitive(json_tree_part, "hardware_content_size");
        cJSON *last_modification_in_unix_time = cJSON_GetObjectItemCaseSensitive(json_tree_part, "last_modification_in_unix_time");
        cJSON *content_size = cJSON_GetObjectItemCaseSensitive(json_tree_part, "content_size");
        cJSON *is_binary = cJSON_GetObjectItemCaseSensitive(json_tree_part, "is_binary");
        cJSON *content = cJSON_GetObjectItemCaseSensitive(json_tree_part, "content");

        
        struct DtwTreePart *part = dtw_tree_part_constructor(
            path->valuestring,
            false,
            false
        );
        if(original_path != NULL){
            part->path->original_path = (char *)realloc(part->path->original_path,strlen(original_path->valuestring)+1);
            strcpy(part->path->original_path,original_path->valuestring);
        }

        if(hardware_sha != NULL){
            part->content_exist_in_hardware = true;
            part->hawdware_content_sha = (char *)realloc(part->hawdware_content_sha,strlen(hardware_sha->valuestring)+1);
            strcpy(part->hawdware_content_sha,hardware_sha->valuestring);
            
        }

        if(hardware_content_size != NULL){
            part->content_exist_in_hardware = true;
            part->hardware_content_size = hardware_content_size->valueint;
        }
        
        if(last_modification_in_unix_time != NULL){
            part->last_modification_time = last_modification_in_unix_time->valueint;
        }
    
        if(is_binary != NULL){
            part->is_binary = is_binary->valueint;
        }
        
        if(content_size != NULL){
            part->content_size = content_size->valueint;
        }

        if(content != NULL){
            part->content_exist_in_memory = true;
            if(!content_size){
                part->content_size = strlen(content->valuestring);
            }
            if(part->is_binary){
                size_t out_size;
                unsigned char *decoded =dtw_base64_decode(
                    (unsigned char*)content->valuestring,
                    part->content_size,&out_size
                );
                part->set_binary_content(part,decoded,out_size);
                free(decoded);
            }
           else{
                part->set_string_content(part,content->valuestring);
           } 
        }
        self->add_tree_part_by_reference(self,part);
        
    }
    cJSON_Delete(json_tree);
}

char * private_dtw_dumps_tree_json(struct DtwTree *self,bool preserve_content,bool preserve_path_atributes,bool preserve_hadware_data,bool preserve_content_data,bool minify){
    
    cJSON *json_array = cJSON_CreateArray();
    for(int i = 0; i < self->size; i++){
       
        cJSON *json_tree_part = cJSON_CreateObject();
        struct DtwTreePart *tree_part = self->tree_parts[i];
        char *path_string = tree_part->path->get_path(tree_part->path);
        

        cJSON_AddItemToObject(
            json_tree_part, 
            "path", 
            cJSON_CreateString(path_string)
        );
        
        
        
        if(preserve_path_atributes == true){

                char *dir_string = tree_part->path->get_dir(tree_part->path);
                char *full_name_string = tree_part->path->get_full_name(tree_part->path);
                char *name_string = tree_part->path->get_name(tree_part->path);
                char *extension_string = tree_part->path->get_extension(tree_part->path);    
                if(tree_part->path->original_path != path_string){
                    cJSON_AddItemToObject(
                        json_tree_part, 
                        "original_path", 
                        cJSON_CreateString(tree_part->path->original_path)
                    );
                }

                cJSON_AddItemToObject(
                    json_tree_part, 
                    "dir", 
                    cJSON_CreateString(dir_string)
                );
                
                cJSON_AddItemToObject(
                    json_tree_part, 
                    "full_name", 
                    cJSON_CreateString(full_name_string)
                );
                
                cJSON_AddItemToObject(
                    json_tree_part, 
                    "name", 
                    cJSON_CreateString(name_string)
                );
                
                cJSON_AddItemToObject(
                    json_tree_part, 
                    "extension", 
                    cJSON_CreateString(extension_string)
                );

                free(dir_string);
                free(full_name_string);
                free(name_string);
                free(extension_string);
        }


        if(preserve_hadware_data== true && tree_part->content_exist_in_hardware){
            cJSON_AddItemToObject(
                json_tree_part, 
                "hardware_sha256", 
                cJSON_CreateString(tree_part->hawdware_content_sha)
            );
            cJSON_AddItemToObject(
                json_tree_part, 
                "last_modification_in_unix", 
                cJSON_CreateNumber(tree_part->last_modification_time)
            );

            cJSON_AddItemToObject(
                json_tree_part, 
                "hardware_content_size", 
                cJSON_CreateNumber(tree_part->hardware_content_size)
            );
            char *last_modification_string =tree_part->last_modification_time_in_string(tree_part);
            cJSON_AddItemToObject(
                json_tree_part, 
                "last_modification", 
                cJSON_CreateString(last_modification_string)
            );
            
            free(last_modification_string);

            
        }

        if(preserve_content_data && tree_part->content_exist_in_memory){
            char *content_sha = tree_part->get_content_sha(tree_part);
            cJSON_AddItemToObject(
                json_tree_part, 
                "content_size", 
                cJSON_CreateNumber(tree_part->content_size)
            );

            cJSON_AddItemToObject(
                json_tree_part, 
                "content_sha256", 
                cJSON_CreateString(content_sha)
            );

            free(content_sha);
        }

        if(preserve_content && tree_part->content_exist_in_memory){

            cJSON_AddItemToObject(
                json_tree_part, 
                "is_binary", 
                cJSON_CreateBool(tree_part->is_binary)
            );  
            if(tree_part->is_binary == false){
                cJSON_AddItemToObject(
                    json_tree_part, 
                    "content", 
                    cJSON_CreateString(tree_part->get_content_string_by_reference(tree_part))
                );
            }
            else{
                unsigned char *content_base64 = dtw_base64_encode(tree_part->content, tree_part->content_size);
                char *content_base64_string = (char *)content_base64;
                cJSON_AddItemToObject(
                    json_tree_part, 
                    "content", 
                    cJSON_CreateString(content_base64_string)
                );  
                free(content_base64);
            }
        }
       

        //Add json_tree_part  
        cJSON_AddItemToArray(json_array,json_tree_part);
        free(path_string);

    }
    
    char *json_string = cJSON_Print(json_array);
    //set ident to 4 spaces
    if(minify == true){
        cJSON_Minify(json_string);
    }
    cJSON_Delete(json_array);
    return json_string;
}