

DtwLocker *newDtwLocker(const char *shared_lock_file){


    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));
    self->shared_lock_file = strdup(shared_lock_file);

    self->process = getpid();

    return self;
}

void DtwLocker_create_shared_file(const char *location, long max_lock_time){
    cJSON *central = cJSON_CreateObject();
    const char *TIME = "t";
    const char *ELEMENTS = "e";
    cJSON_AddNumberToObject(central,TIME,(double)max_lock_time);
    cJSON *elements = cJSON_CreateArray();
    cJSON_AddItemToObject(central,ELEMENTS,elements);
    char *printed = cJSON_PrintUnformatted(central);
    dtw_write_string_file_content(location,printed);
    cJSON_Delete(central);
    free(printed);
}


int DtwLocker_lock(struct DtwLocker *self, const  char *element,int time){

    DtwLockerStream  *stream = privatenewDtwLockerStream(self->shared_lock_file);

    const char *TIME = "t";
    const char *ELEMENTS = "e";
    const char *PROCESS = "p";
    const char *FILE  = "f";
    const char *LAST_UPDATE = "l";

    cJSON *timeout = cJSON_GetObjectItem(stream->elements,TIME);
    if(timeout->type != cJSON_Number){
        privatenewDtwLockerStream_free(stream);
        return DTW_FILE_NOT_CORRECT;
    }

    cJSON *elements = cJSON_GetObjectItem(stream->elements,ELEMENTS);
    if(elements->type != cJSON_Array){
        privatenewDtwLockerStream_free(stream);
        return DTW_FILE_NOT_CORRECT;
    }
    cJSON *created_locked = cJSON_CreateObject();
    cJSON_AddNumberToObject(created_locked,PROCESS,self->process);
    cJSON_AddStringToObject(created_locked,FILE, element);
    long now = time(NULL);
    cJSON_AddNumberToObject(created_locked,LAST_UPDATE, (double)now);
    cJSON_AddItemToArray(elements,created_locked);


    privatenewDtwLockerStream_set_elements(stream,elements);
    privatenewDtwLockerStream_free(stream);



}

void DtwLocker_unlock(struct DtwLocker *self, const  char *element){

}


void DtwLocker_free(struct DtwLocker *self){
    free(self->shared_lock_file);
    free(self);
}