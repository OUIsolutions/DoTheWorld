


struct  DtwTree * dtw_tree_constructor(){
    struct DtwTree *self = (struct DtwTree*)malloc(sizeof(struct DtwTree));
    self->size = 0;
    self->tree_parts = (struct DtwTreePart**)malloc(1);
    self->add_tree_part_by_copy = private_dtw_add_tree_part_copy;
    self->add_tree_part_by_reference = private_dtw_add_tree_part_reference;
    self->delete_tree = private_dtw_delete_tree;
    self->represent = private_dtw_represent_tree;
    self->add_path_from_hardware = private_dtw_add_path_from_hardware;
    self->dumps_tree_json = private_dtw_dumps_tree_json;
    return self;
}


void private_dtw_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = tree_part->copy_tree_part(tree_part);
       
}
void private_dtw_add_tree_part_reference(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = tree_part;
}


void private_dtw_delete_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->delete_tree_part(self->tree_parts[i]);
    }
    free(self->tree_parts);
    
    free(self);
}

void private_dtw_represent_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->represent(self->tree_parts[i]);
    }
}
void private_dtw_add_path_from_hardware(struct DtwTree *self,const char *path,bool load_content, bool preserve_content){
    
    struct DtwStringArray *path_array = dtw_list_all_recursively(path, true);
    for(int i = 0; i < path_array->size; i++){
        const char *current_path = path_array->strings[i];

        
        struct DtwTreePart *tree_part = dtw_tree_part_constructor(
            current_path,
            load_content,
            preserve_content
        );
        self->add_tree_part_by_reference(self, tree_part);
        
    }

    path_array->delete_string_array(path_array);

}
 
char * private_dtw_dumps_tree_json(struct DtwTree *self,bool preserve_content,bool preserve_path_atributes,bool preserve_hadware_data,bool generate_content_sha256,bool minify){
    
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
            char *last_modification_string =dtw_convert_unix_time_to_string(tree_part->last_modification_time);
            cJSON_AddItemToObject(
                json_tree_part, 
                "last_modification", 
                cJSON_CreateString(last_modification_string)
            );
            free(last_modification_string);

            
        }
        if(preserve_content && tree_part->content_exist_in_memory){
            cJSON_AddItemToObject(
                json_tree_part, 
                "content", 
                cJSON_CreateString(tree_part->content)
            );
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