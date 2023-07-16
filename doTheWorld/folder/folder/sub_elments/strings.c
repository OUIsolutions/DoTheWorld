//
// Created by jurandi on 06-07-2023.
//
char * DtwFolder_get_string(struct DtwFolder *self, const char *name, DtwFolderProps *props){
    DtwFolderProps formated_props = DtwFolderProps_create_props(props);

    char *path = private_DtwFolder_create_path(self,name);
    long size;
    bool is_binary;

    unsigned char *result = dtw_load_any_content(path,&size,&is_binary);


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
    if(is_binary){
        self->error = DTW_WRONG_TYPE;
        return NULL;
    }


    free(path);



    if(formated_props.garbage == DTW_ALLOW_GARBAGE){
        self->garbage_array->append(self->garbage_array,DTW_STRING,result);
    }

    return result;

}

void DtwFolder_set_string(struct DtwFolder *self, const char *name, const char *value) {
    char *path = private_DtwFolder_create_path(self, name);
    dtw_write_string_file_content(path,value);
    free(path);
}

