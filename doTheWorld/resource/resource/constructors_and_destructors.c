
DtwResource *private_new_DtwResource_raw(){
    DtwResource *self = (DtwResource*) malloc(sizeof (DtwResource));
    *self =(DtwResource){0};

    self->lock = DtwResource_lock;
    self->set_binary =DtwResource_set_binary;
    self->set_string = DtwResource_set_string;
    self->set_long = DtwResource_set_long;
    self->set_double = DtwResource_set_double;
    self->set_bool = DtwResource_set_bool;
    self->destroy = DtwResource_destroy;

    self->get_any = DtwResource_get_any;
    self->get_binary = DtwResource_get_binary;
    self->get_string = DtwResource_get_string;
    self->get_long = DtwResource_get_long;
    self->get_double =DtwResource_get_double;
    self->get_bool = DtwResource_get_bool;
    self->sub_resource =DtwResource_sub_resource;
    self->commit = DtwResource_commit;
    self->represent = DtwResource_represent;
    self->free = DtwResource_represent;
    self->free = DtwResource_free;
    self->list = DtwResource_list;
    self->type = DtwResource_type;
    self->rename = DtwResource_rename;
    self->type_in_str = DtwResource_type_in_str;


    return self;
}

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = private_new_DtwResource_raw();

    self->path = strdup(path);
    self->name = strdup(path);

    self->allow_transaction = true;
    self->transaction = newDtwTransaction();
#ifdef __linux__
    self->locker = newDtwLocker();
#endif

}

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *name){

    DtwResource *new_element = private_new_DtwResource_raw();
    new_element->allow_transaction = self->allow_transaction;
    new_element->transaction = self->transaction;
    new_element->child = true;
    new_element->mothhers_path = strdup(self->path);
    new_element->path = dtw_concat_path(self->path, name);
    new_element->name = strdup(name);

    new_element->locked = self->locked;
    new_element->auto_lock = self->auto_lock;
#ifdef __linux__
    new_element->locker = self->locker;
#endif
    private_DtwResource_lock_if_auto_lock(new_element);
    return new_element;

}


void DtwResource_free(struct DtwResource *self){
    if(!self->child){
        if(self->transaction){
            self->transaction->free(self->transaction);
        }

#ifdef  __linux__
        self->locker->free(self->locker);
#endif
    }

    if(self->mothhers_path){
        free(self->mothhers_path);
    }

    free(self->path);
    free(self->name);
    free(self);
}