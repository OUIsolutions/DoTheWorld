//
// Created by jurandi on 06-07-2023.
//
char * DtwObject_get_string(struct DtwObject *self,const char *name,DtwObjectProps *props){
    DtwObjectProps formated_props = DtwObjectProps_create_props(props);

    char *path = private_DtwObject_create_path(self,name);

    bool load_result = true;
    char *result_text = NULL;

    if(formated_props.cache == DTW_ALLOW_CACHE){
        DtwKeyVal  *keyval = self->loaded_elements->get(
                self->loaded_elements,
                name
         );
         if(keyval){

             if(keyval->type == DTW_STRING){
                 printf("fez a leitura da HEAP\n");

                 result_text = (char*)keyval->any_value;
                load_result = false;
             }
             else{
                 self->error = DTW_WRONG_TYPE;
                 free(path);
                 return NULL;
             }

         }

    }

    if(load_result){
        printf("fez a leitura do disco\n");
        int size;
        bool is_binary;
        unsigned char *possible_string = dtw_load_any_content(path,&size,&is_binary);

        if(possible_string ==  NULL){
            int entity = dtw_entity_type(path);

            if(entity == DTW_FOLDER_TYPE){
                self->error = DTW_WRONG_TYPE;
                free(path);
                return NULL;
            }
            if(entity == DTW_NOT_FOUND){
                self->error = DTW_NOT_FOUND;
                free(path);
                return NULL;
            }
        }
        if(is_binary){
            free(possible_string);
            self->error = DTW_WRONG_TYPE;
            free(path);
            return NULL;
        }
        result_text = (char*)possible_string;

        //making the first upload
        if(formated_props.cache == DTW_ALLOW_CACHE){

            DtwKeyVal *keyval = newDtwKeyVal(name,result_text,DTW_STRING,0);
            self->loaded_elements->append(
                    self->loaded_elements,
                    keyval
            );
            self->garbage_array->append(self->garbage_array, DTW_STRING, result_text);

        }
    }
    free(path);

    return result_text;

}

void DtwObject_set_string(struct DtwObject *self,const char *name, const char *value,DtwObjectProps *props) {

    DtwObjectProps formated_props = DtwObjectProps_create_props(props);
    char *path = private_DtwObject_create_path(self, name);
    dtw_write_string_file_content(path,value);
    free(path);

}