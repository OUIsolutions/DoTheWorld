

DtwResource *private_new_DtwResource_raw(){
    DtwResource *self = (DtwResource*) malloc(sizeof (DtwResource));
    *self =(DtwResource){0};

    self->lock = DtwResource_lock;
    self->set_binary =DtwResource_set_binary;
    self->set_string = DtwResource_set_string;
    self->set_long = DtwResource_set_long;
    self->set_double = DtwResource_set_double;
    self->set_bool = DtwResource_set_bool;


    self->get_any = DtwResource_get_any;
    self->get_binary = DtwResource_get_binary;
    self->get_string = DtwResource_get_string;
    self->get_long = DtwResource_get_long;
    self->get_double =DtwResource_get_double;
    self->get_bool = DtwResource_get_bool;
    self->sub_resource =DtwResource_sub_resource;
    self->commit = DtwResource_commit;
    self->free = DtwResource_free;

    self->type = DtwResource_type;
    self->type_in_str = DtwResource_type_in_str;


    return self;
}

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = private_new_DtwResource_raw();
    self->path = strdup(path);
    self->allow_transaction = true;
    self->transaction = newDtwTransaction();
#ifdef __linux__
    self->locker = newDtwLocker();
#endif

}

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *path){

    DtwResource *new_element = private_new_DtwResource_raw();
    new_element->transaction = self->transaction;
    new_element->child = true;
    new_element->path = dtw_concat_path(self->path,path);
    new_element->locked = self->locked;
    new_element->auto_lock = self->auto_lock;
    #ifdef __linux__
    new_element->locker = self->locker;
    #endif
    private_DtwResource_lock_if_auto_lock(new_element);
    return new_element;

}

void DtwResource_lock(DtwResource *self){
    if(self->locked){
        return;
    }

    #ifdef __linux__
        self->locker->lock(self->locker,self->path);
    #endif
}
void private_DtwResource_lock_if_auto_lock(DtwResource *self){
    if(self->auto_lock){
        self->lock(self);
    }
}

void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size){
    if(self->allow_transaction){
        self->transaction->write_any(self->transaction,self->path,element,size,true);
        return;
    }
    dtw_write_any_content(self->path,element,size);
}

void DtwResource_set_string(DtwResource *self,const  char *element){
    if(self->allow_transaction){
        self->transaction->write_string(self->transaction,self->path,element);
        return;
    }
    dtw_write_string_file_content(self->path,element);
}

void DtwResource_set_long(DtwResource *self,long element){
    if(self->allow_transaction){
        self->transaction->write_long(self->transaction,self->path,element);
        return;
    }
    dtw_write_long_file_content(self->path,element);

}

void DtwResource_set_double(DtwResource *self,double element){
    if(self->allow_transaction){
        self->transaction->write_double(self->transaction,self->path,element);
        return;
    }
    dtw_write_double_file_content(self->path,element);
}

void DtwResource_set_bool( DtwResource *self,bool element){
    if(self->allow_transaction){
        self->transaction->write_bool(self->transaction,self->path,element);
        return;
    }
    dtw_write_bool_file_content(self->path,element);
}

unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary){
    private_DtwResource_lock_if_auto_lock(self);
    return dtw_load_any_content(self->path,size,is_binary);
}

unsigned char *DtwResource_get_binary(DtwResource *self, long *size){
    private_DtwResource_lock_if_auto_lock(self);
    return dtw_load_binary_content(self->path,size);
}

char *DtwResource_get_string(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    return dtw_load_string_file_content(self->path);
}

long DtwResource_get_long(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    return dtw_load_long_file_content(self->path);
}

double DtwResource_get_double(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    return dtw_load_double_file_content(self->path);
}

bool DtwResource_get_bool(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    return dtw_load_bool_file_content(self->path);
}

void DtwResource_commit(DtwResource *self){
    self->transaction->commit(self->transaction,NULL);
}

int DtwResource_type(DtwResource *self){
    return dtw_complex_entity_type(self->path);
}

const char * DtwResource_type_in_str(DtwResource *self){
    return dtw_convert_entity(dtw_complex_entity_type(self->path));
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

    free(self->path);
    free(self);
}