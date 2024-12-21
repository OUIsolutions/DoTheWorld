
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end

typedef struct {
    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;
    DtwLocker *locker;
    bool schema_unsafe;
    int error_code;
    char *error_path;
    char *error_message;

}privateDtwResourceRootProps;
