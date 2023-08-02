

DtwResource *new_DtwResource_raw(){
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
    self->free = DtwResource_free;



    return self;
}

DtwResource *new_DtwResource(const char *path){
    DtwResource *self = new_DtwResource_raw();
    self->path = strdup(path);
    self->allow_transaction = true;
    self->transaction = newDtwTransaction();
#ifdef __linux__
    self->locker = newDtwLocker();
#endif
    self->stored_sub_resources = (DtwResource**) malloc(0);

}

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *path);

void DtwResource_lock(DtwResource *self){
    #ifdef __linux__
        self->locker->lock(self->locker,self->path);
    #endif
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

}
void DtwResource_set_double(DtwResource *self,double element){

}
void DtwResource_set_bool( DtwResource *self,bool element){

}

unsigned char *DtwResource_get_any(DtwResource *self, long size, bool is_binary){

}
unsigned char *DtwResource_get_binary(DtwResource *self, long size){

}
char *DtwResource_get_string(DtwResource *self){

}
long DtwResource_get_long(DtwResource *self){

}
double DtwResource_get_double(DtwResource *self){

}
bool DtwResource_get_bool(DtwResource *self){

}

void DtwResource_free(struct DtwResource *self){

}