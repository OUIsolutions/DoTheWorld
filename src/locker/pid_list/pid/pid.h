typedef struct {

    long pid;
    int total_locked;

}DtwLockerPidElement;

DtwLockerPidElement * newDtwLockerPidElement(long pid);

void DtwLockerPidElement_free(DtwLockerPidElement *self);
