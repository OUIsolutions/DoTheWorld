

DtwLocker *newDtwLocker(){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));

    self->process = getpid();
    self->total_checks = 100;
    self->max_lock_time = 10;
    self->locked_elements = newDtwStringArray();

    return self;
}




int  DtwLocker_lock(DtwLocker *self, const char *element) {

    const char *LOCK_FOLDER = ".lock";
    const int LOCK_FOLDER_SIZE = (int)strlen(LOCK_FOLDER);
    char *file = (char*)malloc(strlen(element) +  LOCK_FOLDER_SIZE + 10);
    sprintf(file,"%s%s",element,LOCK_FOLDER);

    while (true){

        long now = time(NULL);
         bool write = false;
         int entity_type = dtw_entity_type(file);
         if(entity_type== DTW_NOT_FOUND){
            write = true;
         }

         else if(entity_type== DTW_FILE_TYPE){
             long last_modification  = dtw_get_entity_last_motification_in_unix(file);
             if ((now - last_modification) > self->max_lock_time) {
                 write = true;
             }
         }

         else{
             free(file);
             return -1;
         }

         if(!write) {
             continue;
         }
        dtw_write_long_file_content(file,self->process);
        for(int i = 0;i < self->total_checks;i++){
            long result = dtw_load_long_file_content(file);
            if(result != self->process){
                continue;
            }
        }

        break;


    }
    
    free(file);
    return 0;

}

void DtwLocker_unlock( DtwLocker *self, const  char *element){
    bool found = false;
    for(long i = 0; i < self->locked_elements->size;i++){
        if(strcmp(self->locked_elements->strings[i],element)==0){
            found = true;
            break;
        }
    }

    if(!found){
        return;
    }


    const char *LOCK_FOLDER = ".lock";
    const int LOCK_FOLDER_SIZE = (int)strlen(LOCK_FOLDER);
    char *file = (char*)malloc(strlen(element) +  LOCK_FOLDER_SIZE + 10);
    sprintf(file,"%s%s",element,LOCK_FOLDER);
    dtw_remove_any(file);
    free(file);
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
    const char *LOCK_FOLDER = ".lock";
    const int LOCK_FOLDER_SIZE = (int)strlen(LOCK_FOLDER);
    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];
        char *file = (char*)malloc(strlen(element) +  LOCK_FOLDER_SIZE + 10);
        sprintf(file,"%s%s",element,LOCK_FOLDER);
        dtw_remove_any(file);
        free(file);
    }

    DtwStringArray_free(self->locked_elements);
    free(self);
}