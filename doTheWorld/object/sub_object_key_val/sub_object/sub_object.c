
DtwSubObject * newDtwSubObject(char *key,void *any_value,int type,int size){
    DtwSubObject  *self = (DtwSubObject*) malloc(sizeof (DtwSubObject));
    self->key = strdup(key);
    self->any_value = any_value;
    self->size = size;
    self->type = type;
    return self;
}

void DtwSubObject_free(DtwSubObject *self){
    if(self->type != DTW_NONE){
        if(self->type == DTW_OBJECT){
            DtwObject *element = (DtwObject*)self->any_value;
            element->free(element);
        }
        else{
            free(self->any_value);
        }
    }
    free(self->key);
    free(self);

}

