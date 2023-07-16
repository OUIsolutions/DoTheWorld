unsigned char * DtwFolder_get_binary_file(struct DtwFolder *self, const char *name, long *size, DtwFolderProps *props){
    DtwFolderProps formated_props = DtwFolderProps_create_props(props);

    char *path = private_DtwFolder_create_path(self,name);
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

void DtwFolder_set_binary_file(struct DtwFolder *self, const char *name, unsigned  char *value, long size){

    char *path = private_DtwFolder_create_path(self, name);
    dtw_write_any_content(path,value,size);


    free(path);

}
