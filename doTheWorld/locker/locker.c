

DtwLocker *newDtwLocker(char *path){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));
    dtw_remove_any(self->path);
    dtw_create_dir_recursively(path);

    self->separator = "|";
    self->path = strdup(path);
    self->process = getpid();
    self->max_lock_time = 5;
    self->reverifcation_delay= 1;
    self->min_interval_delay = 0.3;
    self->max_interval_delay = 0.5;
    //methods
    self->locked_elements = newDtwStringArray();
    self->status = DtwLocker_element_status;
    self->lock = DtwLocker_lock;
    self->unlock = DtwLocker_unlock;
    self->free = DtwLocker_free;
    return self;
}

void private_DtwLocker_format_element(char *result,struct DtwLocker *self,const  char *element){
    unsigned  long element_size = strlen(element);
    unsigned long separator_size = strlen(self->separator);
    sprintf(result,"%s/",self->path);
    unsigned long result_size = strlen(result);
    bool included_separator = false;

    for(unsigned  long i =0; i < element_size;i++){
        char current_char = element[i];

        if(current_char == '/' || current_char == '\\'){

            if(!included_separator){
                strcat(result,self->separator);
                result_size+=separator_size;
                included_separator = true;
            }

        }else{
            included_separator = false;
            result[result_size] = current_char;
            result_size+=1;
        }
    }

    if(dtw_ends_with(result,self->separator)){
        result[result_size-separator_size] = '\0';
    }


}

int DtwLocker_element_status(struct DtwLocker *self, const  char *element){
    
    char formated_element[2000] = {0};
    private_DtwLocker_format_element(formated_element,self,element);
   
    char *data;

    data = dtw_load_string_file_content(formated_element);
    if(!data){
        return DTW_ABLE_TO_LOCK;
    }

    int data_size = strlen(data);
    if(data_size == 0){
        free(data);
        return DTW_ABLE_TO_LOCK;
        
    }
    char last_char = data[data_size -1];
    if(last_char != '|'){
        return DTW_ABLE_TO_LOCK;
    }    

    unsigned long last_modification;
    int process;

    sscanf(data,"%ld %i",&last_modification,&process);
    free(data);
    time_t  now = time(NULL);
    //means its an depreciated lock
    if (last_modification < (now - self->max_lock_time)){
        return DTW_ABLE_TO_LOCK;
    }

    if(process == self->process){
        return DTW_ALREADY_LOCKED_BY_SELF;
    }
    return PRIVATE_DTW_LOCKED_BY_OTHER_PROCESS;
}


void DtwLocker_lock(struct DtwLocker *self, const char *element) {
    char formated_path[2000] = {0};
    private_DtwLocker_format_element(formated_path, self, element);

    bool return_on_end = false;

    while (true) {
        int file = open(formated_path, O_RDWR | O_CREAT, 0644);
        if (file == -1) {
            // Não conseguiu abrir o arquivo, continua tentando
            continue;
        }

        if (flock(file, LOCK_EX ) != -1) {
            printf("process %d bloqueou\n", self->process);

            char *value = dtw_load_string_file_content(formated_path);
            unsigned long last_modification;
            int process;
            sscanf(value, "%ld %i", &last_modification, &process);
            free(value);

            time_t now = time(NULL);
            char content[500] = {0};
            sprintf(content, "%ld %d", now, self->process);
            dtw_write_string_file_content(formated_path, content);

            sleep(4);
            close(file);
            return;


        }
        close(file);
        // Se chegou até aqui, significa que conseguiu bloquear
    }
}

void DtwLocker_unlock(struct DtwLocker *self,const  char *element){
    char formated_element[2000] = {0};
    private_DtwLocker_format_element(formated_element,self,element);

    int status = self->status(self, element);
    if(status == DTW_ALREADY_LOCKED_BY_SELF){
        dtw_remove_any(formated_element);
    }

}

void DtwLocker_free(struct DtwLocker *self){

    for(int i = 0; i < self->locked_elements->size;i++){
        char *current = self->locked_elements->strings[i];
      //  self->unlock(self,current);
    }

    free(self->path);

    self->locked_elements->free(self->locked_elements);
    free(self);
}