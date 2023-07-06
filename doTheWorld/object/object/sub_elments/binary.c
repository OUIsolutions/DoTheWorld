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
