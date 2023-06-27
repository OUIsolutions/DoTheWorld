
DtwSubObject * newDtwSubObject(){
    DtwSubObject  *self = (DtwSubObject*) malloc(sizeof (DtwSubObject));
    self->key = NULL;
    self->number_value = 0;
    self->any_value = NULL;
    self->size = 0;
    self->type = DTW_NONE;
    return self;
}