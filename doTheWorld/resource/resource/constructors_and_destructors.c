

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = (DtwResource*) malloc(sizeof (DtwResource));
    *self =(DtwResource){0};

    self->path = strdup(path);
    self->name = strdup(path);

    self->allow_transaction = true;
    self->transaction = newDtwTransaction();
#ifdef __linux__
    self->locker = newDtwLocker();
#endif
    DtwResource_load(self);
    return self;
}   

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *name,bool load_content){
    DtwResource *new_element = (DtwResource*) malloc(sizeof (DtwResource));
    *new_element =(DtwResource){0};
    new_element->allow_transaction = self->allow_transaction;
    new_element->transaction = self->transaction;
    new_element->child = true;
    new_element->mothers_path = strdup(self->path);
    new_element->path = dtw_concat_path(self->path, name);
    new_element->name = strdup(name);

    new_element->locked = self->locked;
    new_element->auto_lock = self->auto_lock;
#ifdef __linux__
    new_element->locker = self->locker;
#endif
    private_DtwResource_lock_if_auto_lock(new_element);

    if(load_content){
        DtwResource_load(new_element);
    }

    return new_element;

}


void DtwResource_free(struct DtwResource *self){
    if(!self->child){
        if(self->transaction){
            DtwTransaction_free(self->transaction);
        }

#ifdef  __linux__
        DtwLocker_free(self->locker);
#endif
    }

    if(self->mothers_path){
        free(self->mothers_path);
    }
    if(self->value_any){
        free(self->value_any);
    }

    if(self->value_string ){
        free(self->value_string);
    }
    free(self->path);
    free(self->name);
    free(self);
}