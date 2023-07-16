

DtwLocker *newDtwLocker(char *path, int process,int max_lock_time){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));
    self->separator = "|";
    self->path = strdup(path);
    self->process = process;
    self->max_lock_time = max_lock_time;
    //methods
    self->lock = DtwLocker_lock;
    self->unlock = DtwLocker_unlock;
    self->free = DtwLocker_free;
    return self;
}

char *private_DtwLocker_format_element(struct DtwLocker *self,const  char *element){
    unsigned  long element_size = strlen(element);
    unsigned long separator_size = strlen(self->separator);
    char *result = (char*) malloc(2000);
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
    return result;

}
int private_DtwLocker_element_status(struct DtwLocker *self,const  char *element){
    char *data = dtw_load_string_file_content(element);
    if(!data){
        return PRIVATE_DTW_ABLE_TO_LOCK;
    }

    unsigned long last_modification;
    int process;
    if(process == self->process){
        return PRIVATE_DTW_ALREADY_LOCKED_BY_SELF;
    }

    sscanf(data,"%ld %i",&last_modification,&process);
    time_t  now = time(NULL);
    //means its an depreciated lock
    if (last_modification < (now - self->max_lock_time)){
        printf("pegou no time");
        dtw_remove_any(element);
        return PRIVATE_DTW_ABLE_TO_LOCK;
    }
    return PRIVADTE_DTW_LOCKED;
}


bool DtwLocker_lock(struct DtwLocker *self,const  char *element){

}

void DtwLocker_unlock(struct DtwLocker *self,const  char *element){}

void DtwLocker_free(struct DtwLocker *self){}