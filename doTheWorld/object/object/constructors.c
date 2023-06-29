//
// Created by jurandi on 28-06-2023.
//

DtwObject * private_newDtwObject_raw(){

    DtwObject * self = (DtwObject*)malloc(sizeof(DtwObject));
    self->randonizer = NULL;
    self->mode = DTW_BY_REFERENCE;
    self->error =  DTW_OK;
    self->garbage_array = newDtwGarbageArray();
    self->first_object = false;

    self->get_blob = DtwObject_get_blob;
    self->set_blob = DtwObject_set_blob;

    self->get_string = DtwObject_get_string;
    self->get_long = DtwObject_get_long;
    self->get_double = DtwObject_get_double;
    self->sub_object = DtwObject_sub_object;

    self->type_of = DtwObject_type_of;
    self->destroy = DtwObject_destroy;
    self->set_string = DtwObject_set_string;
    self->set_double = DtwObject_set_double;
    self->set_long = DtwObject_set_long;


    self->list_all = DtwObject_list_all;
    self->free = DtwObject_free;
    return  self;
}


DtwObject * newDtwObject(const char *path){
    DtwObject * self = private_newDtwObject_raw();
    self->path = strdup(path);

    self->first_object = true;
    self->randonizer = newDtwRandonizer();
    if(dtw_entity_type(path) ==  DTW_FILE_TYPE){
        dtw_remove_any(path);
    }

    return self;
}