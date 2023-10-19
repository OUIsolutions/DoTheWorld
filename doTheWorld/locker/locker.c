

DtwLocker *newDtwLocker(){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));

    self->process = getpid();

    self->max_lock_time = 5;


    //methods
    self->locked_elements = newDtwStringArray();

    return self;
}



unsigned long long int private_dtw_getMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((unsigned long long int)tv.tv_sec * 1000000) + tv.tv_usec;
}


void DtwLocker_lock(struct DtwLocker *self, const char *element) {


    
    char  *formated_path = (char*)calloc(sizeof(char),strlen(element)+10);
    sprintf(formated_path,"%s.lock",element);


    char process_string[20] = {0};
    sprintf(process_string,"%d",self->process);

    /*
    while(true){
        time_t  now = time(NULL);
        long last_modification = dtw_get_entity_last_motification_in_unix(formated_path);
        bool not_exist = (dtw_entity_type(formated_path) == DTW_NOT_FOUND);
        bool exist = !not_exist;
        bool expired = false;

        if(exist){
            expired = last_modification < (now - self->max_lock_time);
        }

        if(not_exist || expired){
            FILE  *file = fopen()
        }


        if(exist){
            long process_owner = dtw_load_long_file_content(formated_path);
            if(process_owner == self->process ){
                if(DtwStringArray_find_position(self->locked_elements,formated_path) == -1){
                    DtwStringArray_append(self->locked_elements,formated_path);
                    free(formated_path);
                }
                return;
            }
        }

    }
    */





}

void DtwLocker_unlock(struct DtwLocker *self, const  char *element){
    char  *formated_path = (char*)calloc(sizeof(char),strlen(element)+10);
    sprintf(formated_path,"%s.lock",element);
    int position = DtwStringArray_find_position(self->locked_elements,formated_path);

    if(position != -1){
        dtw_remove_any(formated_path);
        DtwStringArray_pop(self->locked_elements,position);
    }

    free(formated_path);

}

void DtwLocker_represemt(struct DtwLocker *self){
    printf("locked:\n");
    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];
        char *unformated = dtw_replace_string(element,".lock","");
        printf("\t%s\n",unformated);
        free(unformated);
    }
}

void DtwLocker_free(struct DtwLocker *self){

    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];

        dtw_remove_any(element);
    }

    DtwStringArray_free(self->locked_elements);
    free(self);
}