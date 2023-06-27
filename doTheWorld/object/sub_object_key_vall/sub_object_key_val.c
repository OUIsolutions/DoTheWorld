
DtwSubObjectArray * newDtwSubObjectArray(){

    DtwSubObjectArray *self = (DtwSubObjectArray*) malloc(sizeof (DtwSubObjectArray));
    self->elements = malloc(0);
    self->size = 0;

    self->append = DtwSubObjectArray_append;
    self->get = DtwSubObjectArray_get;
    self->free = DtwSubObjectArray_free;


}
void DtwSubObjectArray_append(struct DtwSubObjectArray *self,DtwSubObject *object){
    self->elements = (DtwSubObject**) realloc(self->elements,(self->size+1)*sizeof (DtwSubObject*));
    self->elements[self->size] = object;
    self->size+=1;
}

DtwSubObject * DtwSubObjectArray_get(struct DtwSubObjectArray *self, const char *name){
    for(int i = 0; i < self->size;i++){
        DtwSubObject *current = self->elements[i];
        if(strcmp(current->key,name) == 0){
            return current;
        }
    }
    return NULL;
}


void DtwSubObjectArray_free(struct DtwSubObjectArray *self){
    for(int i = 0; i <self->size;i++){
        //free the object here
        free(self->elements[i]);
    }
    free(self);
}

