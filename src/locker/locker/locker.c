

DtwLocker *newDtwLocker(){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));

    self->process = getpid();
    self->total_checks = 10;
    self->max_lock_time = 5;

    self->locked_elements = newDtwStringArray();

    return self;
}




void DtwLocker_lock(DtwLocker *self, const char *element) {

    for(int i = 0;i< self->total_checks; i++){

    }


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