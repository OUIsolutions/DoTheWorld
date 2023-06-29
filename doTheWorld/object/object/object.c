


char * private_DtwObject_create_path(struct DtwObject *self,const char *name){

    if(name){
        char *path = (char*) malloc(strlen(self->path) +strlen(name) + 2);
        sprintf(path,"%s/%s",self->path,name);
        return path;
    }

    for(int i = 0; i  < 30; i++) {

        char *possible_name = self->randonizer->generate_token(self->randonizer, i);
        char *path = (char*)malloc(strlen(self->path) + strlen(possible_name) + 2);
        sprintf(path, "%s/%s", self->path, possible_name);

        free(possible_name);
        if (dtw_entity_type(path) == DTW_NOT_FOUND) {
            return path;
        }
        free(path);


    }
}


DtwObject * DtwObject_sub_object(struct DtwObject *self,const char*name){

    char *path = private_DtwObject_create_path(self,name);
    DtwObject * new_obj = private_newDtwObject_raw();
    new_obj->path = path;
    new_obj->randonizer = self->randonizer;

    if(dtw_entity_type(path) ==  DTW_FILE_TYPE){
        dtw_remove_any(path);
    }

    if(self->mode == DTW_BY_REFERENCE){
        self->garbage_array->append(self->garbage_array,DTW_OBJECT,new_obj);
    }

    return new_obj;

}



void DtwObject_destroy(struct DtwObject *self,const char *name){
    char *path = private_DtwObject_create_path(self,name);
    dtw_remove_any(path);
}

DtwStringArray  * DtwObject_list_all(struct DtwObject *self){

    DtwStringArray  *element = dtw_list_all(self->path,DTW_NOT_CONCAT_PATH);
    if(self->mode == DTW_BY_REFERENCE){
        self->garbage_array->append(self->garbage_array,DTW_STRING_ARRAY,element);
    }
    return element;
}


void DtwObject_free(struct DtwObject *self){


    if(self->first_object){
        self->randonizer->free(self->randonizer);
    }
    self->garbage_array->free(self->garbage_array);
    free(self->path);
    free(self);
}