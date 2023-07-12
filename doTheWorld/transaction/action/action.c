

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
        return "modify file";
    }

    if(self->action == DTW_CREATE_FILE){
        return "create file";
    }

    if(self->action == DTW_CREATE_OR_MODIFY_FILE){
        return "create or modify file";
    }

    if(self->action == DTW_RENAME_FILE){
        return "rename file";
    }

    if(self->action == DTW_REMOVE_FILE){
        return "remove file";
    }

    if(self->action == DTW_CREATE_FOLDER){
        return "create folder";
    }

    if(self->action == DTW_RENAME_FOLDER){
        return "rename folder";
    }

    if(self->action == DTW_REMOVE_FOLDER){
        return "remove folder";
    }

    if(self->action == DTW_RENAME_ANY){
        return "rename any";
    }

    if(self->action == DTW_REMOVE_ANY){
        return "remove any";
    }


}

void DtwTransactionAction_represent(DtwTransactionAction * self){
    printf("action:%s\n",DtwTransactionAction_convert_action(self));
    printf("source1:%s\n", self->source1 ? self->source1 :"null");
    printf("source2:%s\n", self->source2 ? self->source2: "null");
    printf("is binary:%s\n",self->is_binary  ? "true" :"false");

    if(!self->is_binary && self->element){
        printf("element:%s\n",(char*)self->element);
    }
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
