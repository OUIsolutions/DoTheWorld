

DtwActionTransaction * newDtwActionTransaction(){
    DtwActionTransaction *self = (DtwActionTransaction*) malloc(sizeof (DtwActionTransaction));
    *self= (DtwActionTransaction){0};
    return self;
}

DtwActionTransaction * DtwActionTransaction_write_any(unsigned  char *content,long size,bool is_binary){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = PRIVATE_DTW_ACTION_WRITE_ANY;
    memcpy(self->content,content,size);
    self->size = size;
    self->is_binary = is_binary;
    return self;
}


DtwActionTransaction * DtwActionTransaction_move_any(unsigned  char *content,const char *source, const char *dest){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = PRIVATE_DTW_ACTION_MOVE_ANY;
    self->source = strdup(source);
    self->dest = strdup(dest);
    return self;

}

DtwActionTransaction * DtwActionTransaction_copy_any(unsigned  char *content,const char *source, const char *dest){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = PRIVATE_DTW_ACTION_COPY_ANY;
    self->source = strdup(source);
    self->dest = strdup(dest);
    return self;
}

DtwActionTransaction * DtwActionTransaction_delete_any(unsigned  char *content,const char *source){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = PRIVATE_DTW_ACTION_DELETE_ANY;
    self->source = strdup(source);
    return self;
}

void DtwActionTransaction_represent(DtwActionTransaction* self){
    
}


void DtwActionTransaction_free(DtwActionTransaction* self){

    if(self->content){
        free(self->content);
    }
    if(self->source){
        free(self->source);
    }
    if(self->dest){
        free(self->dest);
    }
    free(self);
}
