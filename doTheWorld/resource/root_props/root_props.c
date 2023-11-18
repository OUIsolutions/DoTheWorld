

privateDtwResourceRootProps *newDtwResourceRootProps(){
    privateDtwResourceRootProps *self  = (privateDtwResourceRootProps*) malloc(sizeof (privateDtwResourceRootProps));
    self->transaction = newDtwTransaction();
    self->randonizer = newDtwRandonizer();
    self->locker = newDtwLocker();
    return self;
}


void privateDtwResourceRootProps_free(privateDtwResourceRootProps *self){
    DtwTransaction_free(self->transaction);
    DtwRandonizer_free(self->randonizer);
    DtwLocker_free(self->locker);
    free(self);
}