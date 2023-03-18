struct DtWJsonError * private_dtw_json_error_constructor(){
    struct DtWJsonError *self =(struct DtWJsonError*)malloc(sizeof(struct DtWJsonError));
    self->code = DTW_JSON_ERROR_CODE_OK;
    self->position = 0;
    self->message = "ok";
    self->free_json_error = private_free_json_error;
    return self;
}


struct DtWJsonError * dtw_validate_json_tree(struct DtWJsonError*self, char *content){
 
    struct DtWJsonError *json_error = private_dtw_json_error_constructor();
    cJSON *json_tree = cJSON_Parse(content);
    //verifiy if json_tre is not null
    if(json_tree == NULL){
        json_error->code = DTW_JSON_SYNTAX_ERROR;
        json_error->position = cJSON_GetErrorPtr() - content;
        json_error->message = "json_tree is null";
        return json_error;
    }

    //verifiy if json_tre is an array
    if(!cJSON_IsArray(json_tree)){
        cJSON_Delete(json_tree);
        json_error->code = DTW_JSON_TYPE_ERROR;
        json_error->message = "json_tree is not an array";
        return json_error;
    }
    
    int size = cJSON_GetArraySize(json_tree);
    for(int i = 0; i < size; i++){
        json_error->position = i;
        cJSON *json_tree_part = cJSON_GetArrayItem(json_tree, i);
        cJSON *path = cJSON_GetObjectItemCaseSensitive(json_tree_part, "path");
        cJSON *original_path = cJSON_GetObjectItemCaseSensitive(json_tree_part, "original_path");
        cJSON *hardware_sha = cJSON_GetObjectItemCaseSensitive(json_tree_part, "hardware_sha256");
        cJSON *hardware_content_size = cJSON_GetObjectItemCaseSensitive(json_tree_part, "hardware_content_size");
        cJSON *last_modification_in_unix_time = cJSON_GetObjectItemCaseSensitive(json_tree_part, "last_modification_in_unix_time");
        cJSON *content_size = cJSON_GetObjectItemCaseSensitive(json_tree_part, "content_size");
        cJSON *is_binary = cJSON_GetObjectItemCaseSensitive(json_tree_part, "is_binary");
        cJSON *content = cJSON_GetObjectItemCaseSensitive(json_tree_part, "content");
   
        //path is required
        if(!cJSON_IsString(path)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_KEY_ERROR;
            json_error->message = "path is not a string";
            return json_error;
        }

        //Others are not required
        if(original_path != NULL && !cJSON_IsString(original_path)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_VALUE_ERROR;
            json_error->message = "original_path is not a string";
            return json_error;
        }
        if(hardware_sha != NULL && !cJSON_IsString(hardware_sha)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_VALUE_ERROR;
            json_error->message = "hardware_sha is not a string";
            return json_error;
        }
        if(hardware_content_size != NULL && !cJSON_IsNumber(hardware_content_size)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_VALUE_ERROR;
            json_error->message = "hardware_content_size is not a number";
            return json_error;
        }  
        if(last_modification_in_unix_time != NULL && !cJSON_IsNumber(last_modification_in_unix_time)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_VALUE_ERROR;
            json_error->message = "last_modification_in_unix_time is not a number";
            return json_error;
        }
        if(content_size != NULL && !cJSON_IsNumber(content_size)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_VALUE_ERROR;
            json_error->message = "content_size is not a number";
            return json_error;
        }

        if(is_binary != NULL && !cJSON_IsBool(is_binary)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_VALUE_ERROR;
            json_error->message = "is_binary is not a bool";
            return json_error;
        }
        if(content != NULL && !cJSON_IsString(content)){
            cJSON_Delete(json_tree);
            json_error->code = DTW_JSON_REQUIRED_VALUE_ERROR;
            json_error->message = "content is not a string";
            return json_error;
        }
        
    }
    cJSON_Delete(json_tree);
    return json_error;
}



void private_free_json_error(struct DtWJsonError *self){
    free(self);
}