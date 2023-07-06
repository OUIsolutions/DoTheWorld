
DtwObjectDict * newDtwObjectDict(){

    DtwObjectDict *self = (DtwObjectDict*) malloc(sizeof (DtwObjectDict));
    self->elements = malloc(0);
    self->size = 0;

    self->append = DtwObjectDict_append;
    self->get = DtwObjectDict_get;
    self->free = DtwObjectDict_free;


}
void DtwObjectDict_append(struct DtwObjectDict *self, DtwKeyVal *object){
    self->elements = (DtwKeyVal**) realloc(self->elements, (self->size + 1) * sizeof (DtwKeyVal*));
    self->elements[self->size] = object;
    self->size+=1;
}

DtwKeyVal * DtwObjectDict_get(struct DtwObjectDict *self, const char *name){
    for(int i = 0; i < self->size;i++){
        DtwKeyVal *current = self->elements[i];
        if(strcmp(current->key,name) == 0){
            return current;
        }
    }
    return NULL;
}


void DtwObjectDict_free(struct DtwObjectDict *self){
    for(int i = 0; i <self->size;i++){
        //free the object here
        DtwKeyVal_free(self->elements[i]);
    }
    free(self->elements);
    free(self);
}

