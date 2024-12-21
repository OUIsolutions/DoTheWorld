
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.typesg.h"
//silver_chain_scope_end


typedef struct DtwJsonTransactionErrorModule{
    void (*represent)(struct DtwJsonTransactionError *self);
    void (*free)(struct DtwJsonTransactionError *self);

}DtwJsonTransactionErrorModule;
