

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
    self->type_in_str = DtwResource_type_in_str;


    return self;
}

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = private_new_DtwResource_raw();
    self->name = strdup(path);
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
    new_element->mother = self;
    new_element->name = strdup(path);
    new_element->locked = self->locked;
    new_element->auto_lock = self->auto_lock;
    #ifdef __linux__
    new_element->locker = self->locker;
    #endif
    private_DtwResource_lock_if_auto_lock(new_element);
    return new_element;

}

char * private_DtwResource_get_path(DtwResource *self){
    if(self->child){
        return private_DtwResource_get_path(self->mother);
    }
    return strdup(self->name);
}


void DtwResource_lock(DtwResource *self){
    if(self->locked){
        return;
    }

    #ifdef __linux__
        char *path = private_DtwResource_get_path(self);
        self->locker->lock(self->locker,path);
        free(path);
    #endif
}
void private_DtwResource_lock_if_auto_lock(DtwResource *self){
    if(self->auto_lock){
        self->lock(self);
    }
}

void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size){
    char *path = private_DtwResource_get_path(self);

    if(self->allow_transaction){
        self->transaction->write_any(self->transaction,path,element,size,true);
    }
    else{
        dtw_write_any_content(path,element,size);
    }

    free(path);

}

void DtwResource_set_string(DtwResource *self,const  char *element){
    char *path = private_DtwResource_get_path(self);
    if(self->allow_transaction){
        self->transaction->write_string(self->transaction,path,element);
    }
    else{
        dtw_write_string_file_content(path,element);
    }
    free(path);

}

void DtwResource_set_long(DtwResource *self,long element){
    char *path = private_DtwResource_get_path(self);
    if(self->allow_transaction){
        self->transaction->write_long(self->transaction,path,element);
    }
    else{
        dtw_write_long_file_content(path,element);
    }
    free(path);

}

void DtwResource_set_double(DtwResource *self,double element){
    char *path = private_DtwResource_get_path(self);

    if(self->allow_transaction){
        self->transaction->write_double(self->transaction,path,element);
    }
    else{
        dtw_write_double_file_content(path,element);
    }
    free(path);
}

void DtwResource_set_bool( DtwResource *self,bool element){
    char *path = private_DtwResource_get_path(self);

    if(self->allow_transaction){
        self->transaction->write_bool(self->transaction,path,element);
    }
    else{
        dtw_write_bool_file_content(path,element);
    }
    free(path);
}

void DtwResource_destroy(DtwResource *self){
    char *path = private_DtwResource_get_path(self);

    if(self->allow_transaction){
        self->transaction->delete_any(self->transaction,path);
    }
    else{
        dtw_remove_any(path);
    }
    free(path);
}

unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);

    unsigned char *result = dtw_load_any_content(path,size,is_binary);
    free(path);
    return result;
}

unsigned char *DtwResource_get_binary(DtwResource *self, long *size){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    unsigned  char *result = dtw_load_binary_content(path,size);
    free(path);
    return result;
}

char *DtwResource_get_string(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    char *result = dtw_load_string_file_content(path);
    free(path);
    return result;
}

long DtwResource_get_long(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    long result =  dtw_load_long_file_content(path);
    free(path);
    return result;
}

double DtwResource_get_double(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    double result =  dtw_load_double_file_content(path);
    free(path);
    return result;
}

bool DtwResource_get_bool(DtwResource *self){
    private_DtwResource_lock_if_auto_lock(self);
    char *path = private_DtwResource_get_path(self);
    bool result = dtw_load_bool_file_content(path);
    free(path);
    return result;
}

void DtwResource_commit(DtwResource *self){
    self->transaction->commit(self->transaction,NULL);
}

int DtwResource_type(DtwResource *self){
    char *path = private_DtwResource_get_path(self);
    int type_element =  dtw_complex_entity_type(path);
    free(path);
    return type_element;
}

DtwStringArray *DtwResource_list(DtwResource *self){
    char *path = private_DtwResource_get_path(self);
    DtwStringArray  *result = dtw_list_all(path,DTW_NOT_CONCAT_PATH);
    free(path);
    return result;
}

const char * DtwResource_type_in_str(DtwResource *self){
     return dtw_convert_entity(self->type(self));
}

void DtwResource_represent(DtwResource *self){
    char *path = private_DtwResource_get_path(self);
    printf("path: %s\n", path);
    printf("name: %s\n",self->name);
    printf("type: %s\n",self->type_in_str(self));
    free(path);
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
    free(self->name);
    free(self);
}