


DtwGarbage * newDtwObjectGarbage(int type, void *value){
    DtwGarbage *self = (DtwGarbage*) malloc(sizeof (DtwGarbage));
    self->type = type;
    self->value = value;
}


void DtwObjectGarbage_free(struct DtwGarbage *self){

    if(self->type == DTW_STRING){
        free(self->value);
    }

    if(self->type == DTW_OBJECT){
        DtwObject * element = (DtwObject*)self->value;
        element->free(element);
    }

    if(self->type == DTW_STRING_ARRAY){
        DtwStringArray *element =(DtwStringArray*)self->value;
        element->free(element);
    }

    free(self);
}

