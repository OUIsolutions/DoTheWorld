

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = (DtwResource*) malloc(sizeof (DtwResource));
    *self =(DtwResource){0};

    self->path = strdup(path);
    self->name = strdup(path);
    self->sub_resources = newDtwResourceArray();
    self->allow_transaction = true;
    self->transaction = newDtwTransaction();
#ifdef __linux__
    self->locker = newDtwLocker();
#endif
    DtwResource_load(self);
    return self;
}   

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *name){

    DtwResource * Already_Exist = DtwResourceArray_get_by_name((DtwResourceArray*)self->sub_resources,name);
    if(Already_Exist){
        return Already_Exist;
    }

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
    new_element->sub_resources = newDtwResourceArray();
    DtwResourceArray_append((DtwResourceArray*)self->sub_resources,new_element);

    return new_element;

}


void DtwResource_free(DtwResource *self){



    if(!self->child){
        if(self->transaction){
            DtwTransaction_free(self->transaction);
        }

    #ifdef  __linux__
            DtwLocker_free(self->locker);
    #endif
    }

    DtwResourceArray_free((DtwResourceArray*)self->sub_resources);


    if(self->mothers_path){
        free(self->mothers_path);
    }
    if(self->value_any){
        free(self->value_any);
    }
    free(self->path);
    free(self->name);
    free(self);
}