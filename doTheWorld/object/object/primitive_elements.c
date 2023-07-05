
unsigned char * DtwObject_get_binary(struct DtwObject *self, const char *name, int *size,DtwObjectProps *props){
    DtwObjectProps formated_props = DtwObjectProps_create_props(props);

    char *path = private_DtwObject_create_path(self,name);
    unsigned char *result =dtw_load_binary_content(path,size);

    if(result == NULL){
        if(dtw_entity_type(path) == DTW_FOLDER_TYPE){
            self->error  = DTW_WRONG_TYPE;
        }
        else{
            self->error = DTW_NOT_FOUND;

        }
        free(path);
        return NULL;
    }

    free(path);



    if(formated_props.garbage == DTW_ALLOW_GARBAGE){
        self->garbage_array->append(self->garbage_array,DTW_STRING,result);
    }

    return result;


}

void DtwObject_set_binary(struct DtwObject *self, const char *name, unsigned  char *value, int size,DtwObjectProps *props){
    DtwObjectProps formated_props = DtwObjectProps_create_props(props);
    char *path = private_DtwObject_create_path(self, name);
    dtw_write_any_content(path,value,size);


    free(path);

}

char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectProps *props){
    DtwObjectProps formated_props = DtwObjectProps_create_props(props);

    char *path = private_DtwObject_create_path(self,name);
    int size;
    bool is_binary;
    bool load_result;
    char *result_text;

    if(formated_props.update_cache == DTW_NOT_UPDATE_CACHE){
        load_result = true;
    }

    else if(formated_props.cache == DTW_ALLOW_CACHE){

    }
    unsigned  char *result = dtw_load_any_content(path,&size,&is_binary);

    if(result == NULL){
        if(dtw_entity_type(path) == DTW_FOLDER_TYPE){
            self->error = DTW_WRONG_TYPE;
        }
        else{
            self->error = DTW_NOT_FOUND;
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

    if(formated_props.garbage == DTW_ALLOW_GARBAGE){
        self->garbage_array->append(self->garbage_array, DTW_BINARY, result);
    }

    return (char*)result;

}

void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value,DtwObjectProps *props) {

    DtwObjectProps formated_props = DtwObjectProps_create_props(props);
    char *path = private_DtwObject_create_path(self, name);
    dtw_write_string_file_content(path,value);
    free(path);

}

long DtwObject_get_long(struct DtwObject *self, const char *name,DtwObjectProps *props){
    DtwObjectProps formated_props = DtwObjectProps_create_props(props);
    char *result = self->get_string(self,name,&dtw_no_store);

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

void DtwObject_set_long(struct DtwObject *self,const char *name, long value,DtwObjectProps *props){
    char result[20] = {0};
    sprintf(result,"%li",value);
    self->set_string(self,name,result,NULL);
}


double DtwObject_get_double(struct DtwObject *self, const char *name,DtwObjectProps *props){

    char *result = self->get_string(self,name,&dtw_no_store);

    if(result){

        double result_converted;
        int test = sscanf(result,"%lf",&result_converted);
        free(result);
        if(test == 0){
            self->error = DTW_WRONG_TYPE;
            return 0;
        }
        return result_converted;

    }
    return 0;
}



void DtwObject_set_double(struct DtwObject *self,const char *name, double value,DtwObjectProps *props){
    DtwObjectProps formated_props = DtwObjectProps_create_props(props);
    char result[20] = {0};
    sprintf(result,"%f",value);
    self->set_string(self,name,result,NULL);
}
