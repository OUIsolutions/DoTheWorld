
short DtwActionTransaction_convert_action_in_integer(char *action){
    if(strcmp(action,"write") == 0){
        return DTW_ACTION_WRITE;
    }

    if(strcmp(action,"move") == 0){
        return DTW_ACTION_MOVE;
    }

    if(strcmp(action,"copy") == 0){
        return DTW_ACTION_COPY;
    }

    if(strcmp(action,"delete") == 0){
        return DTW_ACTION_DELETE;
    }

}

char * DtwActionTransaction_convert_action_in_string(int action){
    if(action == DTW_ACTION_WRITE){
        return "write";
    }
    if(action == DTW_ACTION_MOVE){
        return "move";
    }

    if(action == DTW_ACTION_COPY){
        return "copy";
    }
    if(action == DTW_ACTION_DELETE){
        return "delete";
    }

}
cJSON *  private_DtwActionTransaction_create_json_object(DtwActionTransaction* self){
    cJSON * json_object = cJSON_CreateObject();
    cJSON_AddStringToObject(json_object,"action",DtwActionTransaction_convert_action_in_string(self->action_type));

    cJSON_AddStringToObject(json_object,"source",self->source);
    if(self->action_type ==DTW_ACTION_WRITE){
        if(self->is_binary){
            char *converted = dtw_base64_encode(self->content,self->size);
            cJSON_AddStringToObject(json_object,"content",converted);
            free(converted);
            cJSON_AddBoolToObject(json_object,"is binary",true);
        }
        else{
            cJSON_AddStringToObject(json_object,"content",(char*)self->content);
        }
    }
    if(self->action_type != DTW_ACTION_DELETE){
        cJSON_AddStringToObject(json_object,"dest",self->dest);
    }

    return json_object;
}

DtwActionTransaction * private_DtwActionTransaction_parse_json_object(cJSON *json_obj){
    DtwActionTransaction  *self = newDtwActionTransaction();

    char *action = cJSON_GetObjectItem(json_obj,"action")->valuestring;
    self->action_type  = DtwActionTransaction_convert_action_in_integer(action);

    char *source = cJSON_GetObjectItem(json_obj,"source")->valuestring;
    self->source = strdup(source);

    if(self->action_type == DTW_ACTION_DELETE){
        return self;
    }

    if(self->action_type == DTW_ACTION_WRITE){
        self->is_binary = cJSON_GetObjectItem(json_obj,"is binary")->valueint;

        char *content = cJSON_GetObjectItem(json_obj,"content")->valuestring;
        if(self->is_binary){
            self->content = dtw_base64_decode(content,&self->size);
        }
        else{
            self->content =(unsigned char*)strdup(content);
            self->size =(long)strlen(content);
        }

        return self;
    }
    char *dest  = cJSON_GetObjectItem(json_obj,"dest")->valuestring;
    self->dest = strdup(dest);
    return self;
}


void DtwActionTransaction_represent(DtwActionTransaction* self){

    printf("\taction: %s\n", DtwActionTransaction_convert_action_in_string(self->action_type));
    printf("\tsource:%s\n",self->source);
    if(self->action_type == DTW_ACTION_WRITE){

        if(!self->is_binary){
            printf("\tcontent : %s\n",(char*)self->content);
        }
        else{
            printf("\tcontent: impossible to show\n");
        }

        printf("\tsize:%ld\n",self->size);
        printf("\tis binary: %s\n",self->is_binary? "true":"false");
        return;
    }

    if(self->action_type != DTW_ACTION_DELETE){
        printf("\tdest: %s\n",self->dest);
    }

}

