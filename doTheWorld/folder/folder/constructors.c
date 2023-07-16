//
// Created by jurandi on 28-06-2023.
//

DtwFolder * private_newDtwFolder_raw(){

    DtwFolder * self = (DtwFolder*) malloc(sizeof(DtwFolder));
    self->randonizer = NULL;
    self->error =  DTW_OK;
    self->garbage_array = newDtwGarbageArray();
    self->first_object = false;


    self->get_binary = DtwFolder_get_binary;
    self->set_binary = DtwFolder_set_binary;

    self->get_string = DtwFolder_get_string;
    self->set_string = DtwFolder_set_string;

    self->get_long = DtwFolder_get_long;
    self->set_long = DtwFolder_set_long;

    self->set_double = DtwFolder_set_double;
    self->get_double = DtwFolder_get_double;

    self->sub_object = DtwFolder_sub_object;

    self->type_of = DtwFolder_type_of;
    self->inspect_type = DtwFolder_inspect_type;
    self->destroy = DtwFolder_destroy;


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
    if(dtw_entity_type(path) ==  DTW_FILE_TYPE){
        dtw_remove_any(path);
    }

    return self;
}