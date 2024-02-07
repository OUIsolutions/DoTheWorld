

DtwLocker *newDtwLocker(){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));

    self->process = getpid();
    self->total_checks = 10;
    self->max_lock_time = 5;

    self->locked_elements = newDtwStringArray();

    return self;
}




int  DtwLocker_lock(DtwLocker *self, const char *element) {

    const char *LOCK_FOLDER = ".lock";
    const int LOCK_FOLDER_SIZE = (int)strlen(LOCK_FOLDER);
    long now = time(NULL);
    for(int i = 0;i< self->total_checks; i++){

        char *file = (char*)malloc(strlen(element) +  LOCK_FOLDER_SIZE + 10);
        sprintf(file,"%s/%s/%d",element,LOCK_FOLDER,i);
        int entity = dtw_entity_type(file);
        bool write = false;
        if(entity == DTW_NOT_FOUND){
            write = true;
        }
        else if(entity == DTW_FILE_TYPE){
            long last_modification = dtw_get_entity_last_motification_in_unix(file);
            if(last_modification + self->max_lock_time < now){
                write = true;
            }
        }
        else{
            free(file);
            return -1;
        }

        if(write){
            dtw_write_long_file_content(file,self->process);
        }
        free(file);

    }

    return 0;


}

void DtwLocker_unlock( DtwLocker *self, const  char *element){


}

void DtwLocker_represemt( DtwLocker *self){
    printf("locked:\n");
    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];
        char *unformated = dtw_replace_string(element,".lock","");
        printf("\t%s\n",unformated);
        free(unformated);
    }
}

void DtwLocker_free( DtwLocker *self){

    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];

        dtw_remove_any(element);
    }

    DtwStringArray_free(self->locked_elements);
    free(self);
}