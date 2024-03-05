

privateFlockLockedElement * private_new_privateFlockLockedElement(const char *filename,int file_descriptor){
    privateFlockLockedElement *self = (privateFlockLockedElement*) malloc(sizeof (privateFlockLockedElement));
    self->filename = strdup(filename);
    self->file_descriptor = file_descriptor;
    return  self;
}

void privateFlockLockedElement_represent(privateFlockLockedElement *self){
    printf("\tfile: %s",self->filename);
    printf("\tif: %d",self->file_descriptor);

}
void privateFlockLockedElement_free(privateFlockLockedElement *self){
    free(self->filename);
    free(self);

}