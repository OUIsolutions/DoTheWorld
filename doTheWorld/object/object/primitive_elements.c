
unsigned char * DtwObject_get_blob(struct DtwObject *self,const char *name,int *size){

    char *path = private_DtwObject_create_path(self,name);
    unsigned char *result =dtw_load_binary_content(path,size);

    if(result == NULL){
        if(dtw_entity_type(path) == DTW_FOLDER_TYPE){
            self->error  = DTW_WRONG_TYPE;
        }
        else{
            self->error = DTW_OBJECT_NOT_EXIST;

        }
        free(path);
        return NULL;
    }

    free(path);



    if(self->mode == DTW_BY_REFERENCE){
        self->garbage_array->append(self->garbage_array,DTW_STRING,result);
    }

    return result;


}

void DtwObject_set_blob(struct DtwObject *self,const char *name,unsigned  char *value,int size){

    char *path = private_DtwObject_create_path(self, name);
    dtw_write_any_content(path,value,size);

    free(path);

}

char * DtwObject_get_string(struct DtwObject *self,const char *name){

    char *path = private_DtwObject_create_path(self,name);
    int size;
    bool is_binary;
    unsigned  char *result = dtw_load_any_content(path,&size,&is_binary);

    if(result == NULL){
        if(dtw_entity_type(path) == DTW_FOLDER_TYPE){
            self->error = DTW_WRONG_TYPE;
        }
        else{
            self->error = DTW_OBJECT_NOT_EXIST;

        }
        free(path);
        return NULL;
    }

    free(path);

    if(is_binary){
        free(result);
        self->error = DTW_WRONG_TYPE;
        return NULL;
    }



    if(self->mode == DTW_BY_REFERENCE){
        self->garbage_array->append(self->garbage_array,DTW_BLOB,result);
    }

    return (char*)result;

}

void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value) {

    char *path = private_DtwObject_create_path(self, name);
    dtw_write_string_file_content(path,value);
    free(path);

}

long DtwObject_get_long(struct DtwObject *self, const char *name){
    int old_mode = self->mode;
    self->mode = DTW_BY_OWNERSHIP;
    char *result = self->get_string(self,name);
    self->mode = old_mode;


    if(result){
        long result_converted;
        int test = sscanf(result,"%li",&result_converted);
        free(result);
        if(test == 0){
            self->error = DTW_WRONG_TYPE;
            return 0;
        }
        return result_converted;
    }

    return 0;
}

void DtwObject_set_long(struct DtwObject *self,const char *name, long value){
    char result[20] = {0};
    sprintf(result,"%li",value);
    self->set_string(self,name,result);
}


double DtwObject_get_double(struct DtwObject *self, const char *name){
    int old_mode = self->mode;
    self->mode = DTW_BY_OWNERSHIP;
    char *result = self->get_string(self,name);
    self->mode = old_mode;

    if(result){

        double result_converted;
        int test = sscanf(result,"%lf",&result_converted);
        free(result);
        if(test == 0){
            self->mode = DTW_WRONG_TYPE;
            return 0;
        }
        return result_converted;

    }
    return 0;
}



void DtwObject_set_double(struct DtwObject *self,const char *name, double value){
    char result[20] = {0};
    sprintf(result,"%f",value);
    self->set_string(self,name,result);
}
