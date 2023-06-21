
DtwObject * private_newDtwObject_raw(){
    DtwObject * self = (DtwObject *)malloc(sizeof(DtwObject *));

    self->get_long = DtwObject_get_long;
    self->get_float = DtwObject_get_float;
    self->get_string = DtwObject_get_string;
    self->sub_object = DtwObject_sub_object;
    self->unique_random_sub_object = DtwObject_unique_random_sub_object;

    self->set_string = DtwObject_set_string;
    self->set_float = DtwObject_set_float;
    self->set_long = DtwObject_set_long;
    return  self;
}

DtwObject * newDtwObject(const char *path){
    DtwObject * self = private_newDtwObject_raw();
    self->path = strdup(path);
}
char * DtwObject_get_string(struct DtwObject *self,const char *name){
    
}
long DtwObject_get_long(struct DtwObject *self, const char *name);
float DtwObject_get_float(struct DtwObject *self, const char *name);
char * DtwObject_get_string(struct DtwObject *self,const char *name);


void DtwObject_set_long(struct DtwObject *self, long value);
void DtwObject_set_float(struct DtwObject *self, float value);
void DtwObject_set_string(struct DtwObject *self, const char *value);

DtwObject * DtwObject_unique_random_sub_object(DtwObject *self);
DtwObject * DtwObject_sub_object(DtwObject *self,const char *name);
