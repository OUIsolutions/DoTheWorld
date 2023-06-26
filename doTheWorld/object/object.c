
DtwObject * private_newDtwObject_raw(){

    DtwObject * self = (DtwObject*)malloc(sizeof(DtwObject));
    self->randonizer = NULL;
    self->first_object = false;

    self->get_string = DtwObject_get_string;
    self->get_long = DtwObject_get_long;
    self->get_double = DtwObject_get_double;
    self->sub_object = DtwObject_sub_object;


    self->destroy = DtwObject_destroy;
    self->set_string = DtwObject_set_string;
    self->set_double = DtwObject_set_double;
    self->set_long = DtwObject_set_long;


    self->list_all = DtwObject_list_all;

    self->free = DtwObject_free;
     return  self;
}


DtwObject * newDtwObject(const char *path){
    DtwObject * self = private_newDtwObject_raw();
    self->path = strdup(path);
    self->first_object = true;
    self->randonizer = newDtwRandonizer();
    dtw_create_dir_recursively(path);
    return self;
}

char * private_DtwObject_create_path(struct DtwObject *self,const char *name){

    if(name){
        char *path = (char*) malloc(strlen(self->path) +strlen(name) + 2);
        sprintf(path,"%s/%s",self->path,name);
        return path;
    }

    for(int i = 0; i  < 30; i++) {
        char *possible_name = self->randonizer->generate_token(self->randonizer, i);
        char *path = (char *) malloc(strlen(self->path) + strlen(possible_name) + 2);
        sprintf(path, "%s/%s", self->path, possible_name);
        free(possible_name);
        if (dtw_entity_type(path) == DTW_NOT_FOUND) {
            return path;
        }
        free(path);
    }
}

char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectError *error){
    char *path = private_DtwObject_create_path(self,name);
    char *result = dtw_load_string_file_content(path);
    free(path);
    if(result == NULL){
        *error = DTW_OBJECT_NOT_EXIST;
    }
    return result;
}

void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value) {
    char *path = private_DtwObject_create_path(self, name);
    dtw_write_string_file_content(path,value);
    free(path);
}

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
        char result[20] = {0};
        sprintf(result,"%li",value);
        self->set_string(self,name,result);
}


double DtwObject_get_double(struct DtwObject *self, const char *name, DtwObjectError *error){
    char *result = self->get_string(self,name,error);
    if(result){
        double result_converted;
        int test = sscanf(result,"%lf",&result_converted);
        free(result);
        if(test == 0){
            *error = DTW_WRONG_TYPE;
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


DtwObject * DtwObject_sub_object(struct DtwObject *self,const char *name){

    char *path = private_DtwObject_create_path(self,name);
    DtwObject * new_obj = private_newDtwObject_raw();
    new_obj->path = path;
    dtw_create_dir_recursively(path);
    return new_obj;

}



void DtwObject_destroy(struct DtwObject *self,const char *name){
    char *path = private_DtwObject_create_path(self,name);
    dtw_remove_any(path);
}

DtwStringArray  * DtwObject_list_all(struct DtwObject *self){
    return dtw_list_all(self->path,DTW_NOT_CONCAT_PATH);
}


void DtwObject_free(struct DtwObject *self){

    if(self->first_object){
        self->randonizer->free(self->randonizer);
    }

    free(self->path);
    free(self);
}