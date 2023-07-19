

DtwLocker *newDtwLocker(){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));

    self->separator = "|";
    self->process = getpid();

    self->max_lock_time = 5;
    self->reverifcation_delay= 1;

    //methods
    self->locked_elements = newDtwStringArray();
    self->lock = DtwLocker_lock;
    self->free = DtwLocker_free;
    return self;
}






void DtwLocker_lock(struct DtwLocker *self, const char *element) {

    char formated_path[2000] = {0};
    sprintf(formated_path,"%s.lock",element);

    char process_string[20] = {0};
    sprintf(process_string,"%d",self->process);
    int total_fails = 0;

    while(true){
        time_t  now = time(NULL);

        long last_modification = dtw_get_file_last_motification_in_unix(formated_path);
        bool not_exist = (dtw_entity_type(formated_path) == DTW_NOT_FOUND);
        bool exist = !not_exist;
        bool expired = false;

        if(exist){
            expired = last_modification < (now - self->max_lock_time);
        }

        if(not_exist || expired){
            dtw_write_string_file_content(formated_path,process_string);
        }

        if(exist){
            char *content = dtw_load_string_file_content(formated_path);
            if(!content){
                continue;
            }
            int process_owner = atoi(content);
            free(content);

            if(process_owner == self->process ){

                //means the file exist at least one second
                if(last_modification < now -1){
                    printf("process %d esperando ownership\n",self->process);
                    sleep(1);
                    self->locked_elements->append(self->locked_elements,formated_path,DTW_BY_VALUE);
                    return;
                }

            }
            else{
                total_fails+=1;
                sleep(1);
            }
        }

    }

}




void DtwLocker_free(struct DtwLocker *self){

    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];

        dtw_remove_any(element);
    }

    self->locked_elements->free(self->locked_elements);
    free(self);
}