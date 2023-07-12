

DtwTransactionAction * newDtwTransactionAction(
        int action,
        const char *source1,
        const char *source2,
        const char *sha256,
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

    if(sha256){
        self->sha256 = strdup(sha256);
    }

    if(element){
        self->element = (unsigned  char *) malloc(size + 1);
        memccpy(self->element,element,0,size);
    }
    return self;
}




char *DtwTransactionAction_convert_action(DtwTransactionAction *self) {
    switch (self->action) {
        // Escrita
        case DTW_MODIFY_OR_CREATE_FILE:
            return "modify or create file";
        case DTW_MODIFY_FILE:
            return "modify file";
        case DTW_MODIFY_SYNC_FILE:
            return "modify sync file";

            // Renomeamento
        case DTW_RENAME_IF_EXISTE_FILE:
            return "rename if exist file";
        case DTW_RENAME_FILE:
            return "rename file";
        case DTW_RENAME_SYNC_FILE:
            return "rename sync file";

            // Remoção
        case DTW_REMOVE_IF_EXIST_FILE:
            return "remove if exist file";
        case DTW_REMOVE_FILE:
            return "remove file";
        case DTW_REMOVE_SYNC_FILE:
            return "remove sync file";

            // Pastas

            // Criação
        case DTW_CREATE_IF_DONT_EXIST_FOLDER:
            return "create if don't exist folder";
        case DTW_CREATE_FOLDER:
            return "create folder";

            // Renomear
        case DTW_RENAME_IF_EXISTE_FOLDER:
            return "rename if exist folder";
        case DTW_RENAME_FOLDER:
            return "rename folder";

            // Remover
        case DTW_REMOVE_IF_EXIST_FOLDER:
            return "remove if exist folder";
        case DTW_REMOVE_FOLDER:
            return "remove folder";

            // Qualquer
        case DTW_RENAME_ANY_IF_EXIST:
            return "rename any if exist";
        case DTW_RENAME_ANY:
            return "rename any";
        case DTW_REMOVE_ANY_IF_EXIST:
            return "remove any if exist";
        case DTW_REMOVE_ANY:
            return "remove any";

            // Ação desconhecida
        default:
            return "unknown action";
    }
}

void DtwTransactionAction_represent(DtwTransactionAction * self){
    printf("action:%s\n",DtwTransactionAction_convert_action(self));
    printf("source1:%s\n", self->source1 ? self->source1 :"null");
    printf("source2:%s\n", self->source2 ? self->source2: "null");

    if(self->element){
        printf("is binary:%s\n",self->is_binary  ? "true" :"false");
        printf("sha256:%s\n",self->sha256 ? self->sha256 : "null");
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
