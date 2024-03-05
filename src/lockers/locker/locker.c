

DtwLocker *newDtwLocker(){

    DtwLocker *locker = (DtwLocker*)malloc(sizeof(DtwLocker));

#ifdef _WIN32
    locker->locker = newDtwMultiFileLocker();
#endif
    return locker;
}

int DtwLocker_lock(DtwLocker *self, const  char *element){

#ifdef _WIN32
    return DtwMultiFIleLocker_lock(self->locker,element);
#endif
}

void DtwLocker_unlock(DtwLocker *self, const  char *element){
    #ifdef _WIN32
         DtwMultifileLocker_unlock(self->locker,element);
    #endif
}

void DtwLocker_represemt(DtwLocker *self){
#ifdef _WIN32
     DtwMultiFileLocker_represemt(self->locker);
#endif
}

void DtwLocker_free(DtwLocker *self){
#ifdef _WIN32
     DtwMultiFileLocker_free(self->locker);
#endif
    free(self);
}
