


DtwResourceArray * newDtwResourceArray(){
    DtwResourceArray *self = (DtwResourceArray*) malloc(sizeof (DtwResourceArray));
    self->resources = (DtwResource**) malloc(0);
    self->size = 0;
    return self;
}


void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element){
    self->resources = realloc(self->resources,(self->size +1) * sizeof (DtwResource**));
    self->resources[self->size] = element;
    self->size+=1;
}

void DtwResourceArray_pop(DtwResourceArray *self, long position){
    DtwResource_free(self->resources[position]);
    for(long i = position; i < self->size -1; i++){
        self->resources[i] = self->resources[i+1];
    }
}

void DtwResourceArray_free(DtwResourceArray *self, DtwResource *element){
    for(int i = 0; i < self->size; i++){
        DtwResource_free(self->resources[i]);
    }
}
