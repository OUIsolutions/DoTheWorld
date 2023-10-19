

DtwLocker *newDtwLocker(const char *shared_lock_file){

    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));
    self->shared_lock_file = strdup(shared_lock_file);
    self->expiration = 5;
    self->process = getpid();

    return self;
}

void DtwLocker_create_shared_file(const char *location) {
    dtw_write_string_file_content(location,"[]");
}
int privateDtwLocker_json_enssure_correct(struct DtwLocker *self, cJSON *elements){
    if(elements->type != cJSON_Array){
        return  DTW_FILE_NOT_CORRECT;
    }
    const int PROCESS = 0;
    const int FILE = 1;
    const int LAST_UPDATE = 2;
    int size = cJSON_GetArraySize(elements);
    for(int i =0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(elements,i);
        if(current->type != cJSON_Array){
            return DTW_FILE_NOT_CORRECT;
        }
        int element_size = cJSON_GetArraySize(current);
        if(element_size != 3){
            return DTW_FILE_NOT_CORRECT;
        }
        cJSON *process = cJSON_GetArrayItem(current,PROCESS);
        if(process->type != cJSON_Number){
            return DTW_FILE_NOT_CORRECT;
        }
        cJSON *file = cJSON_GetArrayItem(current,FILE);
        if(file->type != cJSON_String){
            return DTW_FILE_NOT_CORRECT;
        }
        cJSON *last_update = cJSON_GetArrayItem(current,LAST_UPDATE);
        if(last_update->type != cJSON_Number){
            return DTW_FILE_NOT_CORRECT;
        }

    }
    return 0;
}
void privateDtwLocker_remove_expireds(struct DtwLocker *self,cJSON *elements){

    const int LAST_UPDATE = 2;
    int size = cJSON_GetArraySize(elements);
    for(int i =0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(elements,i);
        cJSON *last_update = cJSON_GetArrayItem(current,LAST_UPDATE);
        long now = time(NULL);
        if(now > last_update->valueint + self->expiration){
            cJSON_DeleteItemFromArray(elements,i);
        }
    }
}
int  privateDtwLocker_get_locked_position_from_json(struct DtwLocker *self,cJSON *elements,const char *element){
    const int FILE = 1;
    int size = cJSON_GetArraySize(elements);
    for(int i =0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(elements,i);
        cJSON *time = cJSON_GetArrayItem(current,FILE);
        if(strcmp(time->valuestring,element) == 0){
            return i;
        }
    }
    return -1;
}


int DtwLocker_lock(struct DtwLocker *self, const  char *element,int max_time){
    long start_time = time(NULL);
    while (true){
        long now_v = time(NULL);
        if(start_time != DTW_WAIT_ALL && start_time !=  DTW_DONT_WAIT){
            if(now_v > start_time + max_time){
                return DTW_TIMEOUT_ERROR;
            }
        }
        DtwLockerStream  *stream = privatenewDtwLockerStream(self->shared_lock_file);
        int error = stream->error;
        if(error){
            privatenewDtwLockerStream_free(stream);
            return error;
        }

        cJSON *elements = stream->elements;
        error = privateDtwLocker_json_enssure_correct(self,elements);
        if(error){
            privatenewDtwLockerStream_free(stream);
            return error;
        }
        privateDtwLocker_remove_expireds(self,elements);
        //means doesnt exist
        bool not_exist = privateDtwLocker_get_locked_position_from_json(self,elements,element)== -1;

        if(not_exist){
            cJSON *created_locked = cJSON_CreateArray();
            cJSON_AddItemToArray(created_locked, cJSON_CreateNumber(self->process));
            cJSON_AddItemToArray(created_locked, cJSON_CreateString(element));
            long now = time(NULL);
            cJSON_AddItemToArray(created_locked,cJSON_CreateNumber(now));
            cJSON_AddItemToArray(elements,created_locked);
            privatenewDtwLockerStream_set_elements(stream,elements);
            return 0;
        }

        privatenewDtwLockerStream_free(stream);

        if(start_time == DTW_DONT_WAIT){
            return DTW_TIMEOUT_ERROR;
        }

    }

    return 0;

}

int DtwLocker_unlock(struct DtwLocker *self, const  char *element){
    DtwLockerStream  *stream = privatenewDtwLockerStream(self->shared_lock_file);
    int error = stream->error;
    if(error){
        privatenewDtwLockerStream_free(stream);
        return error;
    }

    cJSON *elements = stream->elements;
    error = privateDtwLocker_json_enssure_correct(self,elements);
    if(error){
        privatenewDtwLockerStream_free(stream);
        return error;
    }

    int position = privateDtwLocker_get_locked_position_from_json(self,elements,element);

    if(position == -1){
        privatenewDtwLockerStream_free(stream);
        return DTW_ELEMENT_NOT_LOCKED;
    }

    cJSON_DeleteItemFromArray(elements,position);
    privatenewDtwLockerStream_set_elements(stream,elements);
    return 0;
}



void DtwLocker_free(struct DtwLocker *self){
    free(self->shared_lock_file);
    free(self);
}