//
// Created by jurandi on 06-07-2023.
//
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