
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
        case DTW_RENAME_IF_EXIST_FOLDER:
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


int DtwTransactionAction_convert_string(const char *actionString) {
    if (strcmp(actionString, "modify or create file") == 0) {
        return DTW_MODIFY_OR_CREATE_FILE;
    } else if (strcmp(actionString, "modify file") == 0) {
        return DTW_MODIFY_FILE;
    } else if (strcmp(actionString, "modify sync file") == 0) {
        return DTW_MODIFY_SYNC_FILE;
    } else if (strcmp(actionString, "rename if exist file") == 0) {
        return DTW_RENAME_IF_EXISTE_FILE;
    } else if (strcmp(actionString, "rename file") == 0) {
        return DTW_RENAME_FILE;
    } else if (strcmp(actionString, "rename sync file") == 0) {
        return DTW_RENAME_SYNC_FILE;
    } else if (strcmp(actionString, "remove if exist file") == 0) {
        return DTW_REMOVE_IF_EXIST_FILE;
    } else if (strcmp(actionString, "remove file") == 0) {
        return DTW_REMOVE_FILE;
    } else if (strcmp(actionString, "remove sync file") == 0) {
        return DTW_REMOVE_SYNC_FILE;
    } else if (strcmp(actionString, "create if don't exist folder") == 0) {
        return DTW_CREATE_IF_DONT_EXIST_FOLDER;
    } else if (strcmp(actionString, "create folder") == 0) {
        return DTW_CREATE_FOLDER;
    } else if (strcmp(actionString, "rename if exist folder") == 0) {
        return DTW_RENAME_IF_EXIST_FOLDER;
    } else if (strcmp(actionString, "rename folder") == 0) {
        return DTW_RENAME_FOLDER;
    } else if (strcmp(actionString, "remove if exist folder") == 0) {
        return DTW_REMOVE_IF_EXIST_FOLDER;
    } else if (strcmp(actionString, "remove folder") == 0) {
        return DTW_REMOVE_FOLDER;
    } else if (strcmp(actionString, "rename any if exist") == 0) {
        return DTW_RENAME_ANY_IF_EXIST;
    } else if (strcmp(actionString, "rename any") == 0) {
        return DTW_RENAME_ANY;
    } else if (strcmp(actionString, "remove any if exist") == 0) {
        return DTW_REMOVE_ANY_IF_EXIST;
    } else if (strcmp(actionString, "remove any") == 0) {
        return DTW_REMOVE_ANY;
    }
    else {
        // Valor desconhecido, retorna um valor padrão
        return -1;
    }
}
