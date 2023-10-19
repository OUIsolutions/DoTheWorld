
DtwLockerStream * privatenewDtwLockerStream(const char *file){
    DtwLockerStream *self = (DtwLockerStream*) malloc(sizeof (DtwLockerStream));
    *self = (DtwLockerStream){0};
    self->file = fopen(file,"r+");
    if(!file){
        self->error = DTW_FILE_NOT_CORRECT;
        return self;
    }

    self->fd = fileno(self->file);
    int lock_result = flock(self->fd, LOCK_EX);

    if(lock_result != 0){
        self->error = DTW_INTERNAL_ERROR;
        fclose(self->file);
        return self;
    }

    if(fseek(self->file,0,SEEK_END) == -1){
        flock(self->fd, LOCK_UN);
        fclose(self->file);
        self->error= DTW_INTERNAL_ERROR;
        return self;
    }

    long size = ftell(self->file);

    if(size == -1){
        flock(self->fd, LOCK_UN);
        fclose(self->file);
        self->error = DTW_INTERNAL_ERROR;
        return self;
    }

    if(fseek(self->file,0,SEEK_SET) == -1){
        flock(self->fd, LOCK_UN);
        fclose(self->file);
        self->error =DTW_INTERNAL_ERROR;
    }
    char *content = (char*)malloc(size +1);
    long bytes_read = fread(content,sizeof(char),size,self->file);
    if(bytes_read <=0 ){
        free(content);
        flock(self->fd, LOCK_UN);
        fclose(self->file);
        self->error = DTW_INTERNAL_ERROR;
        return self;
    }

    self->elements = cJSON_Parse(content);
    if(!self->elements){
        flock(self->fd, LOCK_UN);
        fclose(self->file);
        self->error = DTW_FILE_NOT_CORRECT;
    }
    free(content);
}

void  privatenewDtwLockerStream_set_elements(DtwLockerStream *self,cJSON *elements){
    char *result  = cJSON_PrintUnformatted(elements);
    fwrite(result,sizeof(char), strlen(result),self->file);
    free(result);
}


void  privatenewDtwLockerStream_free(DtwLockerStream *self){
    if(self->error){
        free(self);
        return;
    }

    flock(self->fd, LOCK_UN);
    fclose(self->file);
    cJSON_Delete(self->elements);
    free(self);
}
