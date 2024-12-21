
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end
#ifndef PRIVATE_DTW_JSON_TRANSACTION_ERROR_TYPE_H
#define PRIVATE_DTW_JSON_TRANSACTION_ERROR_TYPE_H
typedef struct DtwJsonTransactionError{
    int code;
    char *mensage;
    char *path;


}DtwJsonTransactionError;
#endif
