

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
}


