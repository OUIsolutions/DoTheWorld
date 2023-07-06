


DtwGarbageElement * newDtwObjectGarbage(int type, void *value){
    DtwGarbageElement *self = (DtwGarbageElement*) malloc(sizeof (DtwGarbageElement));
    self->type = type;
    self->value = value;
}


void DtwObjectGarbage_free(struct DtwGarbageElement *self){

    if(self->type == DTW_STRING || self->type == DTW_BINARY){
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

