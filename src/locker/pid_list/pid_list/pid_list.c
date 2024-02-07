

DtwLockerPidList * newDtwLockerPidList(){
    DtwLockerPidList *self = (DtwLockerPidList*) malloc(sizeof (DtwLockerPidList));
    self->size = 0;
    self->pids = (DtwLockerPidElement**) malloc(0);
}

void DtwLockerPidList_add_pid(DtwLockerPidList *self,long pid){
    for(int i =0; i  < self->size; i++){
        DtwLockerPidElement *current = self->pids[i];
        if(current->pid ==pid){
            current->total_locked+=1;
            return;
        }
    }

    self->pids =(DtwLockerPidElement**) realloc(
            self->pids,
            (self->size+1) * sizeof (DtwLockerPidElement**)
    );

    DtwLockerPidElement *created = newDtwLockerPidElement(pid);
    self->pids[self->size] = created;
    self->size += 1;

}

long DtwLockerPidList_get_higher_pid(DtwLockerPidList *self){
    DtwLockerPidElement *higher = NULL;

    for(int i =0; i  < self->size; i++){

        DtwLockerPidElement *current = self->pids[i];
        if(i == 0){
            higher = current;
        }
        if(current->total_locked > higher->total_locked){
            higher = current;
        }
    }
    if(higher){
        return higher->pid;
    }
    return -1;
}

void DtwLockerPidList_free(DtwLockerPidList *self){
    for(int i =0; i  < self->size; i++){

        DtwLockerPidElement *current = self->pids[i];
        DtwLockerPidElement_free(current);
    }

    free(self->pids);
    free(self);
}
