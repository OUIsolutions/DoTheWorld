typedef struct {

    int pid;
    int total_locked;

}DtwLockerPidElement;

DtwLockerPidElement * newDtwLockerPidElement(int pid);

void DtwLockerPidElement_free(DtwLockerPidElement *self);
