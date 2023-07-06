
DtwKeyVal * newDtwKeyVal(const char *key, void *any_value, int type, int size){
    DtwKeyVal  *self = (DtwKeyVal*) malloc(sizeof (DtwKeyVal));
    self->key = strdup(key);
    self->any_value = any_value;
    self->size = size;
    self->type = type;
    return self;
}

void DtwKeyVal_free(DtwKeyVal *self){
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

