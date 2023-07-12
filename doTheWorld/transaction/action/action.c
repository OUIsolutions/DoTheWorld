

DtwTransactionAction * newDtwTransactionAction(
        int action,
        const char *source1,
        const char *source2,
        bool is_binary,
        unsigned char *element,
        long size
){

    DtwTransactionAction *self = (DtwTransactionAction*) malloc(sizeof(DtwTransactionAction));
    *self = (DtwTransactionAction){.action = action,.is_binary = is_binary,.size = size};

    if(source1){
        self->source1 = strdup(source1);
    }

    if(source2){
        self->source2 = strdup(source2);
    }

    if(element){
        self->element = (unsigned  char *) malloc(size + 1);
        memccpy(self->element,element,0,size);
    }
    return self;
}

char *DtwTransactionAction_convert_action(DtwTransactionAction * self){
    if(self->action == DTW_MODIFY_FILE){
        return "modify_file";
    }
    if(self->action == )
}
void DtwTransactionAction_free(DtwTransactionAction * self){
    if(self->source1){
        free(self->source1);
    }
    if(self->source2){
        free(self->source2);
    }
    if(self->element){
        free(self->element);
    }
    free(self);
}
