

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
int privateDtwLocker_remove_expireds(struct DtwLocker *self,cJSON *elements){

}
int DtwLocker_lock(struct DtwLocker *self, const  char *element,int max_time){

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


    cJSON *created_locked = cJSON_CreateArray();
    cJSON_AddItemToArray(created_locked, cJSON_CreateNumber(self->process));
    cJSON_AddItemToArray(created_locked, cJSON_CreateString(element));
    long now = time(NULL);
    cJSON_AddItemToArray(created_locked,cJSON_CreateNumber(now));
    cJSON_AddItemToArray(elements,created_locked);

    privatenewDtwLockerStream_set_elements(stream,elements);

    privatenewDtwLockerStream_free(stream);

    return 0;

}

void DtwLocker_unlock(struct DtwLocker *self, const  char *element){

}


void DtwLocker_free(struct DtwLocker *self){
    free(self->shared_lock_file);
    free(self);
}