

DtwActionTransaction * newDtwActionTransaction(){
    DtwActionTransaction *self = (DtwActionTransaction*) malloc(sizeof (DtwActionTransaction));
    *self= (DtwActionTransaction){0};
    return self;
}

DtwActionTransaction * DtwActionTransaction_write_any(const char *source, unsigned  char *content,long size,bool is_binary){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_WRITE;
    self->content = (unsigned char*)malloc(size +2);
    memcpy(self->content,content,size);
    self->content[size] = '\0';
    self->size = size;
    self->source = strdup(source);
    self->is_binary = is_binary;
    return self;
}


DtwActionTransaction * DtwActionTransaction_move_any(const char *source, const char *dest){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_MOVE;
    self->source = strdup(source);
    self->dest = strdup(dest);
    return self;

}

DtwActionTransaction * DtwActionTransaction_copy_any(const char *source, const char *dest){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_COPY;
    self->source = strdup(source);
    self->dest = strdup(dest);
    return self;
}

DtwActionTransaction * DtwActionTransaction_delete_any(const char *source){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_DELETE;
    self->source = strdup(source);
    return self;
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


void DtwActionTransaction_commit(DtwActionTransaction* self,const char *path){

    char *formated_source = dtw_concat_path(path,self->source);


    if(self->action_type == DTW_ACTION_WRITE){
        dtw_write_any_content(formated_source,self->content,self->size);
        free(formated_source);
        return;
    }
    if(self->action_type == DTW_ACTION_DELETE){
        dtw_remove_any(formated_source);
        free(formated_source);
        return;
    }
    char *formated_dest = dtw_concat_path(path,self->dest);

    if(self->action_type == DTW_ACTION_MOVE){
        dtw_move_any(formated_source,formated_dest,DTW_NOT_MERGE);
    }
    if(self->action_type == DTW_ACTION_COPY){
        dtw_copy_any(formated_source,formated_dest,DTW_NOT_MERGE);
    }

    free(formated_dest);
    free(formated_source);

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
            cJSON_AddBoolToObject(json_object,"is binary",false);
        }
        cJSON_AddNumberToObject(json_object,"size",(double)self->size);
    }
    if(self->action_type != DTW_ACTION_DELETE){
        cJSON_AddStringToObject(json_object,"dest",self->dest);
    }

    return json_object;
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


void DtwActionTransaction_free(DtwActionTransaction* self){

    if(self->content){
        free(self->content);
    }
    if(self->source){
        free(self->source);
    }
    if(self->dest){
        free(self->dest);
    }
    free(self);
}
