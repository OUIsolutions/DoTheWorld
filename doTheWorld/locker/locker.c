

DtwLocker *newDtwLocker(){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));

    self->process = getpid();

    self->max_lock_time = 5;
    self->reverifcation_delay= 0.1;
    self->wait_delay = 1;

    //methods
    self->locked_elements = newDtwStringArray();
    self->lock = DtwLocker_lock;
    self->free = DtwLocker_free;
    return self;
}



unsigned long long int getMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((unsigned long long int)tv.tv_sec * 1000000) + tv.tv_usec;
}


void DtwLocker_lock(struct DtwLocker *self, const char *element) {

    char  *formated_path = (char*)calloc(sizeof(char),strlen(element)+10);
    sprintf(formated_path,"%s.lock",element);

    char process_string[20] = {0};
    sprintf(process_string,"%d",self->process);
    int total_fails = 0;
    long verification_deley = (long)(self->reverifcation_delay * 1000000);

    while(true){
        time_t  now = time(NULL);
        unsigned long long startTime = getMicroseconds();
        long last_modification = dtw_get_file_last_motification_in_unix(formated_path);
        bool not_exist = (dtw_entity_type(formated_path) == DTW_NOT_FOUND);


        bool exist = !not_exist;
        bool expired = false;

        if(exist){
            expired = last_modification < (now - self->max_lock_time);
        }

        if(not_exist || expired){

            DtwPath *path = newDtwPath(formated_path);
            char *dirname = DtwPath_get_dir(path);
            if(dirname){
                dtw_create_dir_recursively(dirname);
                free(dirname);
            }
            DtwPath_free(path);

            unsigned long long end_time = getMicroseconds();
            unsigned long long controled_duration = end_time - startTime;

            if(verification_deley != 0){
                if(controled_duration > (long)(verification_deley/2)){
                   // printf("controle de uração excedito\n");
                    continue;
                }
            }

            FILE *file = fopen(formated_path,"wb");
            if(!file){
                continue;
            }
            fwrite(process_string, sizeof(char),strlen(process_string), file);
            fclose(file);
            usleep(verification_deley);
            continue;
        }


        if(exist){
            char *content = dtw_load_string_file_content(formated_path);

            if(!content){
                continue;
            }
            int process_owner = atoi(content);
            free(content);

            if(process_owner == self->process ){
                //printf("process %d get ownership\n",self->process);
                DtwStringArray_append(self->locked_elements,formated_path);
                free(formated_path);
                return;
            }
            else{
                total_fails+=1;
                usleep((long)(self->wait_delay * 1000000));
            }
        }

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