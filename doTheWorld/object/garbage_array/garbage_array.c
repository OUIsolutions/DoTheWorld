

DtwGarbageArray * newDtwGarbageArray(){
    DtwGarbageArray *self = (DtwGarbageArray*) malloc(sizeof (DtwGarbageArray));
    self->elements = malloc(0);
    self->append = DtwGarbageArray_append;
    self->free = DtwGarbageArray_free;
    self->size = 0;

}

void DtwGarbageArray_append(struct DtwGarbageArray *self,int type, void *value){
    self->elements = (DtwObjectGarbage**) realloc(self->elements,(self->size + 1) * sizeof (DtwObjectGarbage*));
    self->elements[self->size] = newDtwObjectGarbage(type,value);
    self->size+=1;
}

void DtwGarbageArray_free(struct DtwGarbageArray *self){
    for(int i = 0; i < self->size; i++){
        DtwObjectGarbage_free(self->elements[i]);

    }
    free(self->elements);
    free(self);
}
