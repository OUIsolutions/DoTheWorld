

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
    char *result = (char*) malloc(2000);
    sprintf(result,"%s/",self->path);
    unsigned long result_size = strlen(result);
    bool included_separator = false;

    for(unsigned  long i =0; i < element_size;i++){
        char current_char = element[i];
        if(current_char == '\\'){
            if(!included_separator){
                strcat(result,self->separator);
                result_size = strlen(result);
                included_separator = true;
            }

        }else{
            included_separator = false;
            result[result_size] = current_char;
            result_size+=1;
        }

    }
}

bool DtwLocker_lock(struct DtwLocker *self,const  char *element){

}


