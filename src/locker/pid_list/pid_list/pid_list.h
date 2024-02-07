typedef struct{

    DtwLockerPidElement **pids;
    int size;

}DtwLockerPidList;

DtwLockerPidList * newDtwLockerPidList();

void DtwLockerPidList_add_pid(DtwLockerPidList *self,long pid);

long DtwLockerPidList_get_higher_pid(DtwLockerPidList *self);

void DtwLockerPidList_free(DtwLockerPidList *self);