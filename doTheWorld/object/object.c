
DtwObject * private_newDtwObject_raw(){
    DtwObject * self = (DtwObject *)malloc(sizeof(DtwObject *));
    self->get_string = DtwObject_get_string;

    self->get_long = DtwObject_get_long;
    self->get_double = DtwObject_get_double;
    self->sub_object = DtwObject_sub_object;
    self->unique_random_sub_object = DtwObject_unique_random_sub_object;

    self->set_string = DtwObject_set_string;
    self->set_double = DtwObject_set_double;
    self->set_long = DtwObject_set_long;

     return  self;
}


DtwObject * newDtwObject(const char *path){
    DtwObject * self = private_newDtwObject_raw();
    self->path = strdup(path);
}

char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectError *error){
    char *path = (char*) malloc(strlen(self->path) +strlen(name) + 2);
    sprintf(path,"%s/%s",self->path,name);
    char *result = dtw_load_string_file_content(path);
    free(path);
    if(result == NULL){
        *error = DTW_OBJECT_NOT_EXIST;
    }
    return result;
}
void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value){
    char *path = (char*) malloc(strlen(self->path) +strlen(name) + 2);
    sprintf(path,"%s/%s",self->path,name);}

long DtwObject_get_long(struct DtwObject *self, const char *name,DtwObjectError *error){
    char *result = self->get_string(self,name,error);
    if(result){
        long result_converted;
        int test = sscanf(result,"%li",&result_converted);
        free(result);
        if(test == 0){
            *error = DTW_WRONG_TYPE;
            return 0;
        }
        return result_converted;
    }
    return 0;
}
void DtwObject_set_long(struct DtwObject *self,const char *name, long value){

}
double DtwObject_get_double(struct DtwObject *self, const char *name, DtwObjectError *error){
    char *result = self->get_string(self,name,error);
    if(result){
        double result_converted;
        int test = sscanf(result,"%f",&result_converted);
        free(result);
        if(test == 0){
            *error = DTW_WRONG_TYPE;
            return 0;
        }
        return result_converted;
    }
    return 0;}



void DtwObject_set_double(struct DtwObject *self,const char *name, double value){

}

DtwObject * DtwObject_unique_random_sub_object(DtwObject *self){

}
DtwObject * DtwObject_sub_object(DtwObject *self,const char *name){

}

DtwObject * DtwObject_free(DtwObject *self){
    free(self->path);
    free(self);
}