
char *DtwTransactionAction_convert_action(DtwTransactionAction *self) {
    switch (self->action) {
        // Escrita

        case DTW_CREATE_FILE:
            return "create file";

        case DTW_MODIFY_OR_CREATE_FILE:
            return "modify or create file";
        case DTW_MODIFY_FILE:
            return "modify file";
        case DTW_MODIFY_SYNC_FILE:
            return "modify sync file";

        case DTW_RENAME_ANY:
            return "rename any";
        case DTW_REMOVE_ANY:
            return "remove any";

        case DTW_COPY_ANY:
            return "copy any";

        default:
            return "unknown action";
    }
}


int DtwTransactionAction_convert_string(const char *actionString) {
    if(strcmp(actionString,"create file") == 0){
        return DTW_CREATE_FILE;
    }

    else if (strcmp(actionString, "modify or create file") == 0) {
        return DTW_MODIFY_OR_CREATE_FILE;

    } else if (strcmp(actionString, "modify file") == 0) {
        return DTW_MODIFY_FILE;
    }

    else if (strcmp(actionString, "modify sync file") == 0) {
        return DTW_MODIFY_SYNC_FILE;
    }

    else if (strcmp(actionString, "rename any") == 0) {
        return DTW_RENAME_ANY;
    }

    else if (strcmp(actionString, "remove any") == 0){
        return DTW_REMOVE_ANY;
    }

    else if(strcmp(actionString, "copy any") == 0){
        return DTW_COPY_ANY;
    }

    else {
        return -1;
    }
}
