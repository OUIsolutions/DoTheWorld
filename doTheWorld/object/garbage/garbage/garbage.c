

DtwGarbage * newDtwGarbageArray(){
    DtwGarbage *self = (DtwGarbage*) malloc(sizeof (DtwGarbage));
    self->elements = malloc(0);
    self->append = DtwGarbageArray_append;
    self->free = DtwGarbageArray_free;
    self->size = 0;

}

void DtwGarbageArray_append(struct DtwGarbage *self, int type, void *value){
    self->elements = (DtwGarbageElement**) realloc(self->elements, (self->size + 1) * sizeof (DtwGarbageElement*));
    self->elements[self->size] = newDtwObjectGarbage(type,value);
    self->size+=1;
}

void DtwGarbageArray_free(struct DtwGarbage *self){
    for(int i = 0; i < self->size; i++){
        DtwObjectGarbage_free(self->elements[i]);

    }
    free(self->elements);
    free(self);
}
