//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end




DtwJsonTransactionError * private_new_DtwJsonTransactionError( int code,const char *mensage,const  char *path);

void DtwJsonTransactionError_represent(struct DtwJsonTransactionError *self);

void DtwJsonTransactionError_prepend_path(struct DtwJsonTransactionError *self,char *path);

void DtwJsonTransactionError_free(struct DtwJsonTransactionError *self);
