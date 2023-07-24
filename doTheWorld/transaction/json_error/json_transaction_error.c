




DtwJsonTransactionError * private_new_DtwJsonTransactionError( int code,const char *mensage,const  char *path){
    DtwJsonTransactionError *self = (DtwJsonTransactionError*) malloc(sizeof(DtwJsonTransactionError));
    self->code  = code;
    self->mensage = strdup(mensage);
    self->path = NULL;
    if(path){
        self->path = strdup(path);
    }
    self->represent = DtwJsonTransactionError_represent;
    self->free = DtwJsonTransactionError_free;
    return self;
}

void DtwJsonTransactionError_represent(struct DtwJsonTransactionError *self){
    printf("code: %d\n",self->code);
    printf("mensage:%s",self->mensage);
    if(self->path){
        printf("path: %s",self->path);
    }
}

void DtwJsonTransactionError_free(struct DtwJsonTransactionError *self){
    free(self->mensage);
    if(self->path){
        free(self->path);
    }
    free(self);
}

