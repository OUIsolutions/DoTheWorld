

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

    const char *TIME = "t";
    const char *ELEMENTS = "e";
    const char *PROCESS = "p";
    const char *FILE  = "f";
    const char *LAST_UPDATE = "l";
    cJSON *elements = stream->elements;
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