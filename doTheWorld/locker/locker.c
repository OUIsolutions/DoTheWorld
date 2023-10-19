

DtwLocker *newDtwLocker(){
    DtwLocker *self = (DtwLocker*) malloc(sizeof (DtwLocker));

    self->process = getpid();

    self->max_lock_time = 5;


    //methods
    self->locked_elements = newDtwStringArray();

    return self;
}



unsigned long long int private_dtw_getMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((unsigned long long int)tv.tv_sec * 1000000) + tv.tv_usec;
}


void DtwLocker_lock(struct DtwLocker *self, const char *element) {


    
    char  *formated_path = (char*)calloc(sizeof(char),strlen(element)+10);
    sprintf(formated_path,"%s.lock",element);


    char process_string[20] = {0};
    sprintf(process_string,"%d",self->process);


    while(true){

        FILE  *file = fopen(formated_path,"r+");
        if(!file){
            printf("pegou aqui 1\n");
            continue;
        }

        int fd = fileno(file);
        int lock_result = flock(fd, LOCK_EX);

        if(lock_result != 0){
            fclose(file);
            continue;
        }

        if(fseek(file,0,SEEK_END) == -1){
            fclose(file);
            printf("pegou aqui2\n");

            continue;

        }


        long size = ftell(file);

        if(size == -1){
            fclose(file);
            printf("pegou aqui3\n");
            continue;
        }


        if(fseek(file,0,SEEK_SET) == -1){
            fclose(file);
            continue;
        }

        if(size == 0){
            printf("escreveu o processo l%d\n",self->process);
            fwrite(process_string, sizeof(char), strlen(process_string),file);
            DtwStringArray_append(self->locked_elements,formated_path);
            free(formated_path);
            fclose(file);

            return;
        }

        char *content = (char*)malloc(size +1);
        long bytes_read = fread(content,sizeof(char),size,file);
        if(bytes_read <=0 ){
            free(content);
            fclose(file);
            continue;
        }
        content[size] = '\0';
        bool is_already_locked_by_same = strcmp(content,process_string) == 0;
        if(is_already_locked_by_same) {
            free(formated_path);
            free(content);
            fclose(file);
            return;
        }

        
        free(content);
        fclose(file);


    }






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