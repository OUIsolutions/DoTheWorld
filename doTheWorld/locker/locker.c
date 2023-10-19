

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

    while (true){
        FILE *file = fopen(formated_path,"r+");
        if(file == NULL){
            file = fopen(formated_path,"w");
            int fd = fileno(file);
            flock(fd, LOCK_EX);
            if(lock == 0){
                continue;
            }
        }
    }
    free(formated_path);






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