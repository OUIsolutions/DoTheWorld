
FlockLocker * newFlockLocker(){

    FlockLocker *self = (FlockLocker*) malloc(sizeof (FlockLocker));
    *self  = (FlockLocker){0};
    self->temp_folder = "/tmp/";
    
    return self;
}

void  FlockLocker_free(FlockLocker *self){
    free(self);
}