
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.macros.h"
//silver_chain_scope_end
#ifndef PRIVATE_DTW_JSON_TREE_ERROR_TYPE_H
#define PRIVATE_DTW_JSON_TREE_ERROR_TYPE_H
typedef struct DtwJsonTreeError {
    int code;
    int position;
    const char *menssage;


}DtwJsonTreeError;
#endif
