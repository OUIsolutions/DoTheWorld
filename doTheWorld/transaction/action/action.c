

DtwActionTransaction * newDtwActionTransaction(){
    DtwActionTransaction *self = (DtwActionTransaction*) malloc(sizeof (DtwActionTransaction));
    *self= (DtwActionTransaction){0};
    return self;
}

DtwActionTransaction * DtwActionTransaction_write_any(const char *dest, unsigned  char *content,long size,bool is_binary){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_WRITE;
    memcpy(self->content,content,size);
    self->size = size;
    self->dest = strdup(dest);
    self->is_binary = is_binary;
    return self;
}


DtwActionTransaction * DtwActionTransaction_move_any(const char *source, const char *dest){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_MOVE;
    self->source = strdup(source);
    self->dest = strdup(dest);
    return self;

}

DtwActionTransaction * DtwActionTransaction_copy_any(const char *source, const char *dest){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_COPY;
    self->source = strdup(source);
    self->dest = strdup(dest);
    return self;
}

DtwActionTransaction * DtwActionTransaction_delete_any(const char *source){
    DtwActionTransaction *self = newDtwActionTransaction();
    self->action_type = DTW_ACTION_DELETE;
    self->source = strdup(source);
    return self;
}

char * DtwActionTransaction_convert_action_in_string(int action){
    if(action == DTW_ACTION_WRITE){
        return "write";
    }
    if(action == DTW_ACTION_MOVE){
        return "move";
    }

    if(action == DTW_ACTION_COPY){
        return "copy";
    }
    if(action == DTW_ACTION_DELETE){
        return "delete";
    }


}


void DtwActionTransaction_represent(DtwActionTransaction* self){

    printf("\taction: %s\n", DtwActionTransaction_convert_action_in_string(self->action_type));
    if(self->action_type == DTW_ACTION_WRITE){

        if(!self->is_binary){
            printf("\tcontent : %s",(char*)self->content);
        }
        else{
            printf("\tcontent: impossible to show\n");
        }

        printf("\tsize:%ld\n",self->size);
        printf("\tis binary: %s\n",self->is_binary? "true":"false");
        printf("\tdest: %s\n",self->dest);
        return;
    }
    printf("\tsource:%s\n",self->source);

    if(self->action_type != DTW_ACTION_DELETE){
        printf("\tdest: %s\n",self->dest);
    }

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
