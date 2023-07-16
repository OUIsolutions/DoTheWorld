//
// Created by jurandi on 28-06-2023.
//

DtwFolder * private_newDtwFolder_raw(){

    DtwFolder * self = (DtwFolder*) malloc(sizeof(DtwFolder));
    self->randonizer = NULL;
    self->error =  DTW_OK;
    self->garbage_array = newDtwGarbageArray();
    self->first_object = false;


    self->get_binary_file = DtwFolder_get_binary_file;
    self->set_binary_file = DtwFolder_set_binary_file;

    self->get_string_file = DtwFolder_get_string_file;
    self->set_string_file = DtwFolder_set_string_file;

    self->get_long_file = DtwFolder_get_long_file;
    self->set_long_file = DtwFolder_set_long_file;

    self->set_double_file = DtwFolder_set_double_file;
    self->get_double_file = DtwFolder_get_double_file;

    self->sub_folder = DtwFolder_sub_folder;

    self->type_of = DtwFolder_type_of;
    self->inspect_type = DtwFolder_inspect_type;
    self->destroy_any = DtwFolder_destroy_any;


    self->size = DtwFolder_size;
    self->list_all = DtwFolder_list_all;
    self->free = DtwFolder_free;
    return  self;
}


DtwFolder * newDtwFolder(const char *path){
    DtwFolder * self = private_newDtwFolder_raw();
    self->path = strdup(path);

    self->first_object = true;
    self->randonizer = newDtwRandonizer();
    int entity_type = dtw_entity_type(path);
    if(entity_type ==  DTW_FILE_TYPE){
        dtw_remove_any(path);
    }
    if(entity_type == DTW_NOT_FOUND){
        dtw_create_dir_recursively(path);
    }

    return self;
}