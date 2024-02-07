typedef struct{

    DtwLockerPidElement **pids;
    int size;

}DtwLockerPidList;

DtwLockerPidList * newDtwLockerPidList();

void DtwLockerPidList_add_pid(DtwLockerPidList *self,int pid);

int DtwLockerPidList_get_higher_pid(DtwLockerPidList *self);

void DtwLockerPidList_free(DtwLockerPidList *self);