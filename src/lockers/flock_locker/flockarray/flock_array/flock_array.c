
privateFlockArray * private_new_privateFlockArray(){
    privateFlockArray * self = (privateFlockArray*) malloc(sizeof (privateFlockArray));
    self->elements = (privateFlockLockedElement **) malloc(0);
    self->size = 0;
}


int  privateFlockArray_index_of(privateFlockArray *self, const char *filename){
    for(int i = 0 ; i <self->size;i++){
        privateFlockLockedElement  *current = self->elements[i];
        if(strcmp(current->filename,filename) ==0){
            return  i;
        }
    }
    return  -1;
}
void privateFlockArray_append(privateFlockArray *self,const char *filename, int file_descriptor){

    self->elements = (privateFlockLockedElement**) realloc(
            self->elements,
            sizeof(privateFlockLockedElement**) * (self->size +1)
            );
    privateFlockLockedElement  *created = private_new_privateFlockLockedElement(filename,file_descriptor);
    self->elements[self->size] = created;
    self->size+=1;
}

void privateFlockArray_destroy_by_index(privateFlockArray *self, int position){
    if(position >= self->size){
        return ;
    }
    privateFlockLockedElement *finded = self->elements[position];
    privateFlockLockedElement_free(finded);
    for(int i = position; i  < self->size-1; i++){
        self->elements[i] = self->elements[i+1];
    }
    self->size-=1;
}


void privateFlockArray_represent(privateFlockArray *self){
    for(int i = 0 ; i <self->size;i++){

        privateFlockLockedElement  *current = self->elements[i];
        printf("=============================\n");
        privateFlockLockedElement_represent(current);
    }
}

void privateFlockArray_free(privateFlockArray *self){
    for(int i = 0 ; i <self->size;i++){
        privateFlockLockedElement  *current = self->elements[i];
        privateFlockLockedElement_free(current);
    }
    free(self->elements);
    free(self);
}