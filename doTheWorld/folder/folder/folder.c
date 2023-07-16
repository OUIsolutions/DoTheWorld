


char * private_DtwFolder_create_path(struct DtwFolder *self, const char *name){

    if(strcmp(name,"$random") == 0){
        for(int i = 20; i  < 30; i++) {

            char *possible_name = self->randonizer->generate_token(self->randonizer, i);
            char *path = (char*)malloc(strlen(self->path) + i + 3);
            sprintf(path, "%s/%s", self->path, possible_name);

            free(possible_name);
            if (dtw_entity_type(path) == DTW_NOT_FOUND) {
                return path;
            }
            free(path);

        }
    }

    if(strcmp(name,"$now") == 0){
        time_t now = time(NULL);
        char *path = (char*)malloc(strlen(self->path) + 30);
        sprintf(path,"%s/%ld",self->path, now);
        return path;
    }


    char *path = (char*) malloc(strlen(self->path) +strlen(name) + 2);
    sprintf(path,"%s/%s",self->path,name);
    return path;



}


DtwFolder * DtwFolder_sub_object(struct DtwFolder *self, const char*name, DtwFolderProps *props){
    DtwFolderProps formated_props = DtwFolderProps_create_props(props);
    char *path = private_DtwFolder_create_path(self,name);
    DtwFolder * new_obj = private_newDtwFolder_raw();
    new_obj->path = path;
    new_obj->randonizer = self->randonizer;

    if(dtw_entity_type(path) ==  DTW_FILE_TYPE){
        dtw_remove_any(path);
    }

    if(formated_props.garbage == DTW_ALLOW_GARBAGE){
        self->garbage_array->append(self->garbage_array,DTW_OBJECT,new_obj);
    }


    return new_obj;

}



void DtwFolder_destroy(struct DtwFolder *self, const char *name){
    char *path = private_DtwFolder_create_path(self,name);
    dtw_remove_any(path);
    free(path);
}

DtwStringArray  * DtwFolder_list_all(struct DtwFolder *self, DtwFolderProps *props){
    DtwFolderProps formated_props = DtwFolderProps_create_props(props);
    DtwStringArray  *element = dtw_list_all(self->path,DTW_NOT_CONCAT_PATH);
    if(formated_props.garbage == DTW_ALLOW_GARBAGE){
        self->garbage_array->append(self->garbage_array,DTW_STRING_ARRAY,element);
    }
    return element;
}

long DtwFolder_size(struct DtwFolder *self){
    DtwStringArray  *elements = self->list_all(self,&dtw_no_store);
    long  size = elements->size;
    elements->free(elements);
    return size;
}


int DtwFolder_type_of(struct DtwFolder *self, const char*name){
    char *path = private_DtwFolder_create_path(self,name);

    int entity = dtw_entity_type(path);
    if(entity != DTW_FILE_TYPE){
        free(path);
        return entity;
    }

    long size;
    bool is_binary;
    unsigned char *result = dtw_load_any_content(path,&size,&is_binary);

    if(is_binary){
        free(result);
        return DTW_BINARY;
    }
    char *result_string = (char*)result;
    double result_converted;
    int test = sscanf(result_string,"%lf",&result_converted);

    if(test == 0){
        free(result);
        return DTW_STRING;
    }
    //verify if its an . inside the result
    int  result_size = (int)strlen(result);
    for(int  i = 0; i < result_size; i++){
        if(result_string[i]== '.'){
            free(result);
            return DTW_DOUBLE;
        }
    }
    free(result);
    return DTW_LONG;

}
char *DtwFolder_inspect_type(struct DtwFolder *self, int type){
    if(type == DTW_FOLDER_TYPE){
        return "Object";
    }
    if(type == DTW_NOT_FOUND){
        return "Not Found";
    }
    if(type == DTW_BINARY){
        return "Binary";
    }

    if(type == DTW_STRING){
        return "String";
    }

    if(type == DTW_LONG){
        return "Long";
    }

    if(type == DTW_DOUBLE){
        return "Double";
    }
}
void DtwFolder_free(struct DtwFolder *self){


    if(self->first_object){
        self->randonizer->free(self->randonizer);
    }
    self->garbage_array->free(self->garbage_array);
    free(self->path);
    free(self);
}