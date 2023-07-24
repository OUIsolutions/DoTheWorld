

DtwJsonTransactionError * dtw_validate_json_transaction(cJSON *json_entry){

}

DtwJsonTransactionError * dtw_validate_json_transaction_file(const char *filename){

}


DtwTransaction * newDtwTransaction_from_json(cJSON *json_entry){
    DtwTransaction *self = newDtwTransaction();
    long size = cJSON_GetArraySize(json_entry);
    for(int i  = 0; i < size; i ++){
        cJSON  *object_action = cJSON_GetArrayItem(json_entry,i);
        DtwActionTransaction  *current_action = private_DtwActionTransaction_parse_json_object(object_action);
        self->append_action(self,current_action);
    }
    return self;
}


DtwTransaction * newDtwTransaction_from_json_file(const char *filename){
    char *content = dtw_load_string_file_content(filename);
    cJSON  *element = cJSON_Parse(content);
    free(content);
    if(!element){
        return NULL;
    }
    DtwTransaction  *self = newDtwTransaction_from_json(element);
    cJSON_Delete(element);
    return self;
}

cJSON * DtwTransaction_dumps_to_json(struct DtwTransaction *self){
    cJSON * json_array = cJSON_CreateArray();
    for(int i =0; i < self->size; i ++){

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

void DtwTransaction_represent(struct DtwTransaction *self){

    for(int i = 0; i < self->size; i++){

        DtwActionTransaction_represent(self->actions[i]);
        printf("------------------------------------\n");

    }

}