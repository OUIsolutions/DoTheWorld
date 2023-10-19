

DtwLocker *newDtwLocker(const char *shared_lock_file){


    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));
    self->shared_lock_file = strdup(shared_lock_file);

    self->process = getpid();

    return self;
}

void dtw_create_lock_shared_file(const char *location,long max_lock_time){
    cJSON *central = cJSON_CreateObject();
    const char *TIME = "t";
    const char *ELEMENTS = "e";
    cJSON_AddNumberToObject(central,TIME,(double)max_lock_time);
    cJSON *elements = cJSON_CreateArray();
    cJSON_AddItemToObject(central,ELEMENTS,elements);
    char *printed = cJSON_PrintUnformatted(central);
    dtw_write_string_file_content(location,printed);
    cJSON_Delete(central);
    free(printed);
}

int DtwLocker_lock(struct DtwLocker *self, const  char *element,int time){


        
        free(content);
        fclose(file);
        flock(fd, LOCK_UN);


}

void DtwLocker_unlock(struct DtwLocker *self, const  char *element){
    char  *formated_path = (char*)calloc(sizeof(char),strlen(element)+10);
    sprintf(formated_path,"%s.lock",element);
    int position = DtwStringArray_find_position(self->locked_elements,formated_path);

    if(position != -1){
        dtw_write_string_file_content(formated_path,"");
        DtwStringArray_pop(self->locked_elements,position);
    }

    free(formated_path);

}

void DtwLocker_represemt(struct DtwLocker *self){
    printf("locked:\n");
    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];
        char *unformated = dtw_replace_string(element,".lock","");
        printf("\t%s\n",unformated);
        free(unformated);
    }
}

void DtwLocker_free(struct DtwLocker *self){

    for(int i = 0 ; i < self->locked_elements->size;i++){
        char *element = self->locked_elements->strings[i];
        dtw_write_string_file_content(element,"");

    }

    DtwStringArray_free(self->locked_elements);
    free(self);
}