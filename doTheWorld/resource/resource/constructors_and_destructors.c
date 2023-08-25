

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = (DtwResource*) malloc(sizeof (DtwResource));
    *self =(DtwResource){0};

    self->path = strdup(path);
    self->name = strdup(path);
    self->sub_resources = newDtwResourceArray();
    self->allow_transaction = true;
    self->cache_sub_resources = true;
    self->transaction = newDtwTransaction();
#ifdef __linux__
    self->locker = newDtwLocker();
#endif
    DtwResource_load(self);
    return self;
}   

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *format, ...){



    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);


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
    new_element->locker = newDtwLocker();
#endif
    private_DtwResource_lock_if_auto_lock(new_element);
    new_element->cache_sub_resources = self->cache_sub_resources;
    new_element->sub_resources = newDtwResourceArray();

    if(self->cache_sub_resources){
        DtwResourceArray_append((DtwResourceArray*)self->sub_resources,new_element);
    }

    return new_element;

}
DtwResource * DtwResource_sub_resource_ensuring_not_exist(DtwResource *self,const  char *format, ...){


    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *possible_emptiy  = DtwResourceArray_get_by_name(
            (DtwResourceArray*)self->sub_resources,
            name
    );
    if(possible_emptiy){
        return NULL;
    }

    bool old_cache_value = self->cache_sub_resources;
    self->cache_sub_resources = false;
    possible_emptiy = DtwResource_sub_resource(self,"%s",name);
    possible_emptiy->cache_sub_resources = old_cache_value;
    self->cache_sub_resources = old_cache_value;

    int type = DtwResource_type(possible_emptiy);

    if(type == DTW_NOT_FOUND){

            if(self->cache_sub_resources){
                DtwResourceArray_append((DtwResourceArray*)self->sub_resources,possible_emptiy);
            }

            return possible_emptiy;
    }

    DtwResource_free(possible_emptiy);
    return  NULL;

}

void DtwResource_free(DtwResource *self){



    if(!self->child){
        if(self->transaction){
            DtwTransaction_free(self->transaction);
        }


    }

#ifdef  __linux__
    DtwLocker_free(self->locker);
#endif
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