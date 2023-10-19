

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


int DtwLocker_lock(struct DtwLocker *self, const  char *element,int max_time){

    DtwLockerStream  *stream = privatenewDtwLockerStream(self->shared_lock_file);
    int error = stream->error;
    if(error){

        privatenewDtwLockerStream_free(stream);
        return error;
    }


    cJSON *elements = stream->elements;

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