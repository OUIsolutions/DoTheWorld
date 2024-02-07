
DtwLockerPidElement * newDtwLockerPidElement(long pid){
    DtwLockerPidElement *self  = (DtwLockerPidElement*) malloc(sizeof (DtwLockerPidElement));
    self->pid = pid;
    self->total_locked = 1;
    return  self;
}

void DtwLockerPidElement_free(DtwLockerPidElement *self){
    free(self);
}