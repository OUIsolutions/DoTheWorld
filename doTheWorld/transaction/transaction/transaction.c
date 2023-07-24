

DtwTransaction * newDtwTransaction(){
    DtwTransaction *self = (DtwTransaction*) malloc(sizeof(DtwTransaction));
    self->actions = (DtwActionTransaction **) malloc(sizeof (DtwActionTransaction**));
    self->size = 0;
    self->append_action =DtwTransaction_append_action;
    self->write_any = DtwTransaction_write_any;
    self->write_string = DtwTransaction_write_string;
    self->move_any = DtwTransaction_move_any;
    self->copy_any = DtwTransaction_copy_any;
    self->delete_any = DtwTransaction_delete_any;
    self->dumps_transaction_to_json =DtwTransaction_dumps_to_json;
    self->dumps_transaction_to_json_file = DtwTransaction_dumps_to_json_file;
    self->commit = DtwTransaction_commit;
    self->represent = DtwTransaction_represent;
    self->free = DtwTransaction_free;
    return self;
}
DtwTransaction * newDtwTransaction_from_json(cJSON *json_entry){
    DtwTransaction *self = newDtwTransaction();
    long size = cJSON_GetArraySize(json_entry);
    for(int i  = 0; i < size; i ++){
        cJSON  *object_action = cJSON_GetArrayItem(json_entry,i);

    }
}

void DtwTransaction_append_action(struct DtwTransaction *self,struct DtwActionTransaction  *action){
    self->actions =  (DtwActionTransaction**)realloc(
            self->actions,
            (sizeof(DtwActionTransaction*) * (self->size+1))
    );
    self->actions[self->size] = action;
    self->size++;
}

DtwTransaction * newDtwTransaction_from_json_file(const char *filename){
    char *content = dtw_load_string_file_content(filename);
    cJSON  *element = cJSON_Parse(content);
    free(content);
    if(!element){
        return NULL;
    }
    DtwTransaction  *self = newDtwTransaction_from_json(element);
    long element_size = cJSON_GetArraySize(element);
    for(long i =0; i <element_size;i++){
        cJSON * current = cJSON_GetArrayItem(element,i);
        DtwActionTransaction  *current_action = private_DtwActionTransaction_parse_json_object(current);
        self->append_action(self,current_action);
    }

    cJSON_Delete(element);
    return self;
}



void DtwTransaction_write_any(struct DtwTransaction *self,const char *path,unsigned char *content, long size,bool is_binary){
    DtwActionTransaction * action = DtwActionTransaction_write_any(path,content,size,is_binary);
    self->append_action(self,action);
}

void DtwTransaction_write_string(struct DtwTransaction *self,const char *path,const char *content){
    DtwActionTransaction * action = DtwActionTransaction_write_any(path,(unsigned char*)content, strlen(content),false);
    self->append_action(self,action);
}

void DtwTransaction_move_any(struct DtwTransaction *self,const char *source,const char *dest){
    DtwActionTransaction * action = DtwActionTransaction_move_any(source,dest);
    self->append_action(self,action);
}

void DtwTransaction_copy_any(struct DtwTransaction *self,const char *source,const char *dest){
    DtwActionTransaction * action = DtwActionTransaction_copy_any(source,dest);
    self->append_action(self,action);
}

void DtwTransaction_delete_any(struct DtwTransaction *self,const char *source){
     DtwActionTransaction  *action = DtwActionTransaction_delete_any(source);
     self->append_action(self,action);
}

cJSON * DtwTransaction_dumps_to_json(struct DtwTransaction *self){
    cJSON * json_array = cJSON_CreateArray();
    for(int i =0; i < self->size; i ++){
        cJSON *created_obj =  private_DtwActionTransaction_create_json_object(self->actions[i]);

        cJSON_AddItemToArray(
                json_array,
                private_DtwActionTransaction_create_json_object(self->actions[i])
        );

    }
    return json_array;
}

void DtwTransaction_dumps_to_json_file(struct DtwTransaction *self,const char *filename){
    cJSON *json_array = self->dumps_transaction_to_json(self);
    char *result = cJSON_Print(json_array);
    dtw_write_string_file_content(filename,result);
    free(result);
    cJSON_Delete(json_array);
}


void DtwTransaction_commit(struct DtwTransaction *self,const char *path){
    for(int i = 0; i < self->size; i++){
        DtwActionTransaction_commit(self->actions[i],path);
    }
}

void DtwTransaction_represent(struct DtwTransaction *self){

    for(int i = 0; i < self->size; i++){
        DtwActionTransaction_represent(self->actions[i]);
        printf("------------------------------------\n");
    }

}

void DtwTransaction_free(struct DtwTransaction *self){
    for(int i =0; i < self->size; i++){
        DtwActionTransaction_free(self->actions[i]);
    }
    free(self->actions);
    free(self);
}
