

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
    self->lock = DtwLocker_lock;
    self->unlock = DtwLocker_unlock;
    self->free = DtwLocker_free;
    return self;
}






void DtwLocker_lock(struct DtwLocker *self, const char *element) {
}

void DtwLocker_unlock(struct DtwLocker *self,const  char *element){

}


void DtwLocker_free(struct DtwLocker *self){

}