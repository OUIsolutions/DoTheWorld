

DtwLocker *newDtwLocker(char *path){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));
    self->separator = "|";
    self->path = strdup(path);
    self->process = getpid();
    self->max_lock_time = 5;
    self->reverifcation_delay= 0.2;
    self->min_interval_delay = 0.1;
    self->max_interval_delay = 0.2;
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
    char *data = dtw_load_string_file_content(element);

    if(!data){
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


bool  DtwLocker_lock(struct DtwLocker *self, const  char *element,double timeout){
    char formated_element[2000] = {0};
    private_DtwLocker_format_element(formated_element,self,element);
    //seed de espera
    srand(time(NULL) + self->process);
    long delay = rand() % (long)(self->max_interval_delay *1000000) +(long)(self->min_interval_delay *1000000);

    double time_spend = 0;

    while (true){

        if(time_spend > timeout && timeout > 0){

            break;
        }


        int status = DtwLocker_element_status(self, formated_element);

        if(status == DTW_ALREADY_LOCKED_BY_SELF){
            return true;
        }

        if(status == DTW_ABLE_TO_LOCK){
            char content[500] = {0};
            time_t  now = time(NULL);
            sprintf(content,"%ld %d",now,self->process);
            dtw_write_string_file_content(formated_element,content);
            //these its nescesserary to make ure the file its able to continue writing
            usleep((long)self->reverifcation_delay* 1000000);
            time_spend+= self->reverifcation_delay;

            int new_status = DtwLocker_element_status(self, formated_element);

            if(new_status == DTW_ALREADY_LOCKED_BY_SELF){
                self->locked_elements->append(self->locked_elements,element,DTW_BY_VALUE);
                return true;
            }

        };
        usleep(delay);
        time_spend+=(double)((double)delay / 1000000);

    }

    return false;

}

void DtwLocker_unlock(struct DtwLocker *self,const  char *element){
    char formated_element[2000] = {0};
    private_DtwLocker_format_element(formated_element,self,element);

    int status = DtwLocker_element_status(self, formated_element);
    if(status == DTW_ALREADY_LOCKED_BY_SELF){
        dtw_remove_any(formated_element);
    }

}

void DtwLocker_free(struct DtwLocker *self){

    for(int i = 0; i < self->locked_elements->size;i++){
        char *current = self->locked_elements->strings[i];
        self->unlock(self,current);
    }
    free(self->path);

    self->locked_elements->free(self->locked_elements);
    free(self);
}