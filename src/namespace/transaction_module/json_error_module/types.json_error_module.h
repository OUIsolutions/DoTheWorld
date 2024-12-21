
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.macros.h"
//silver_chain_scope_end

#ifndef PRIVATE_DTW_JSON_TRANSACTION_MODULE_TYPE_H
#define PRIVATE_DTW_JSON_TRANSACTION_MODULE_TYPE_H
typedef struct DtwJsonTransactionErrorModule{
    void (*represent)(struct DtwJsonTransactionError *self);
    void (*free)(struct DtwJsonTransactionError *self);

}DtwJsonTransactionErrorModule;
#endif
